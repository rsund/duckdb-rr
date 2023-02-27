#include "cpp11.hpp"
#include "duckdb.hpp"
#include "typesr.hpp"
#include "rapi.hpp"

#include "R_ext/Random.h"

#include "duckdb/parser/expression/columnref_expression.hpp"
#include "duckdb/parser/expression/constant_expression.hpp"
#include "duckdb/parser/expression/function_expression.hpp"
#include "duckdb/parser/expression/comparison_expression.hpp"
#include "duckdb/parser/expression/conjunction_expression.hpp"
#include "duckdb/parser/expression/operator_expression.hpp"
#include "duckdb/parser/expression/cast_expression.hpp"
#include "duckdb/parser/expression/case_expression.hpp"

#include "duckdb/main/relation/filter_relation.hpp"
#include "duckdb/main/relation/projection_relation.hpp"
#include "duckdb/main/relation/aggregate_relation.hpp"
#include "duckdb/main/relation/order_relation.hpp"
#include "duckdb/main/relation/join_relation.hpp"
#include "duckdb/main/relation/setop_relation.hpp"
#include "duckdb/main/relation/limit_relation.hpp"
#include "duckdb/main/relation/distinct_relation.hpp"

using namespace duckdb;
using namespace cpp11;

template <typename T, typename... ARGS>
external_pointer<T> make_external(const string &rclass, ARGS &&... args) {
	auto extptr = external_pointer<T>(new T(std::forward<ARGS>(args)...));
	((sexp)extptr).attr("class") = rclass;
	return (extptr);
}

template <typename T, typename... ARGS>
external_pointer<T> make_external_prot(const string &rclass, SEXP prot, ARGS &&... args) {
	auto extptr = external_pointer<T>(new T(std::forward<ARGS>(args)...), true, true, prot);
	((sexp)extptr).attr("class") = rclass;
	return (extptr);
}

// DuckDB Expressions

[[cpp11::register]] SEXP rapi_expr_reference(std::string name, std::string table) {
	if (name.size() == 0) {
		stop("expr_reference: Zero length name");
	}
	if (!table.empty()) {
		auto res = make_external<ColumnRefExpression>("duckdb_expr", name, table);
		res->alias = name; // TODO does this really make sense here?
		return res;
	} else {
		return make_external<ColumnRefExpression>("duckdb_expr", name);
	}
}

[[cpp11::register]] SEXP rapi_expr_constant(sexp val) {
	if (LENGTH(val) != 1) {
		stop("expr_constant: Need value of length one");
	}
	return make_external<ConstantExpression>("duckdb_expr", RApiTypes::SexpToValue(val, 0));
}

[[cpp11::register]] SEXP rapi_expr_function(std::string name, list args) {
	if (name.size() == 0) {
		stop("expr_function: Zero length name");
	}
	vector<unique_ptr<ParsedExpression>> children;
	for (auto arg : args) {
		children.push_back(expr_extptr_t(arg)->Copy());
		// remove the alias since it is assumed to be the name of the argument for the function
		// i.e if you have CREATE OR REPLACE MACRO eq(a, b) AS a = b
		// and a function expr_function("eq", list(expr_reference("left_b", left), expr_reference("right_b", right)))
		// then the macro gets called with eq(left_b=left.left_b, right_b=right.right_b)
		// and an error is thrown. If the alias is removed, the error is not thrown.
		children.back()->alias = "";
	}
	return make_external<FunctionExpression>("duckdb_expr", name, std::move(children));
}

[[cpp11::register]] void rapi_expr_set_alias(duckdb::expr_extptr_t expr, std::string alias) {
	expr->alias = alias;
}

[[cpp11::register]] std::string rapi_expr_tostring(duckdb::expr_extptr_t expr) {
	return expr->ToString();
}

// DuckDB Relations

[[cpp11::register]] SEXP rapi_rel_from_df(duckdb::conn_eptr_t con, data_frame df, bool experimental) {
	if (!con || !con.get() || !con->conn) {
		stop("rel_from_df: Invalid connection");
	}
	if (df.size() == 0) {
		stop("rel_from_df: Invalid data frame");
	}

	named_parameter_map_t other_params;
	other_params["experimental"] = Value::BOOLEAN(experimental);
	auto alias = StringUtil::Format("dataframe_%d_%d", (uintptr_t)(SEXP)df,
	                                (int32_t)(NumericLimits<int32_t>::Maximum() * unif_rand()));
	auto rel =
	    con->conn->TableFunction("r_dataframe_scan", {Value::POINTER((uintptr_t)(SEXP)df)}, other_params)->Alias(alias);

	cpp11::writable::list prot = {df};

	auto res = sexp(make_external_prot<RelationWrapper>("duckdb_relation", prot, std::move(rel)));
	res.attr("df") = df;
	return res;
}

[[cpp11::register]] SEXP rapi_rel_filter(duckdb::rel_extptr_t rel, list exprs) {
	unique_ptr<ParsedExpression> filter_expr;
	if (exprs.size() == 0) { // nop
		warning("rel_filter without filter expressions has no effect");
		return rel;
	} else if (exprs.size() == 1) {
		filter_expr = ((expr_extptr_t)exprs[0])->Copy();
	} else {
		vector<unique_ptr<ParsedExpression>> filters;
		for (expr_extptr_t expr : exprs) {
			filters.push_back(expr->Copy());
		}
		filter_expr = make_unique<ConjunctionExpression>(ExpressionType::CONJUNCTION_AND, std::move(filters));
	}
	auto res = std::make_shared<FilterRelation>(rel->rel, std::move(filter_expr));

	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_project(duckdb::rel_extptr_t rel, list exprs) {
	if (exprs.size() == 0) {
		warning("rel_project without projection expressions has no effect");
		return rel;
	}
	vector<unique_ptr<ParsedExpression>> projections;
	vector<string> aliases;

	for (expr_extptr_t expr : exprs) {
		auto dexpr = expr->Copy();
		aliases.push_back(dexpr->alias.empty() ? dexpr->ToString() : dexpr->alias);
		projections.push_back(std::move(dexpr));
	}

	auto res = std::make_shared<ProjectionRelation>(rel->rel, std::move(projections), std::move(aliases));

	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_aggregate(duckdb::rel_extptr_t rel, list groups, list aggregates) {
	vector<unique_ptr<ParsedExpression>> res_groups, res_aggregates;

	// TODO deal with empty groups
	vector<string> aliases;

	for (expr_extptr_t expr : groups) {
		res_groups.push_back(expr->Copy());
		res_aggregates.push_back(expr->Copy());
	}

	int aggr_idx = 0; // has to be int for - reasons
	auto aggr_names = aggregates.names();

	for (expr_extptr_t expr_p : aggregates) {
		auto expr = expr_p->Copy();
		if (aggr_names.size() > aggr_idx) {
			expr->alias = aggr_names[aggr_idx];
		}
		res_aggregates.push_back(std::move(expr));
		aggr_idx++;
	}

	auto res = std::make_shared<AggregateRelation>(rel->rel, std::move(res_aggregates), std::move(res_groups));

	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_order(duckdb::rel_extptr_t rel, list orders) {
	vector<OrderByNode> res_orders;

	for (expr_extptr_t expr : orders) {
		res_orders.emplace_back(OrderType::ASCENDING, OrderByNullType::NULLS_LAST, expr->Copy());
	}

	auto res = std::make_shared<OrderRelation>(rel->rel, std::move(res_orders));

	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_join(duckdb::rel_extptr_t left, duckdb::rel_extptr_t right, list conds,
                                       std::string join) {
	unique_ptr<ParsedExpression> cond;

	if (conds.size() == 0) { // nop
		stop("join needs conditions");
	} else if (conds.size() == 1) {
		cond = ((expr_extptr_t)conds[0])->Copy();
	} else {
		vector<unique_ptr<ParsedExpression>> cond_args;
		for (expr_extptr_t expr : conds) {
			cond_args.push_back(expr->Copy());
		}
		cond = make_unique<ConjunctionExpression>(ExpressionType::CONJUNCTION_AND, std::move(cond_args));
	}

	auto join_type = JoinType::INNER;
	if (join == "left") {
		join_type = JoinType::LEFT;
	} else if (join == "right") {
		join_type = JoinType::RIGHT;
	} else if (join == "outer") {
		join_type = JoinType::OUTER;
	}
	auto res = std::make_shared<JoinRelation>(left->rel, right->rel, std::move(cond), join_type);

	cpp11::writable::list prot = {left, right};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

static SEXP result_to_df(unique_ptr<QueryResult> res) {
	if (res->HasError()) {
		stop(res->GetError());
	}
	if (res->type == QueryResultType::STREAM_RESULT) {
		res = ((StreamQueryResult &)*res).Materialize();
	}
	D_ASSERT(res->type == QueryResultType::MATERIALIZED_RESULT);
	auto mat_res = (MaterializedQueryResult *)res.get();

	writable::integers row_names;
	row_names.push_back(NA_INTEGER);
	row_names.push_back(-mat_res->RowCount());

	// TODO this thing we can probably statically cache
	writable::strings classes;
	classes.push_back("tbl_df");
	classes.push_back("tbl");
	classes.push_back("data.frame");

	auto df = sexp(duckdb_execute_R_impl(mat_res, false));
	df.attr("class") = classes;
	df.attr("row.names") = row_names;
	return df;
}

[[cpp11::register]] SEXP rapi_rel_union_all(duckdb::rel_extptr_t rel_a, duckdb::rel_extptr_t rel_b) {
	auto res = std::make_shared<SetOpRelation>(rel_a->rel, rel_b->rel, SetOperationType::UNION);

	cpp11::writable::list prot = {rel_a, rel_b};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_limit(duckdb::rel_extptr_t rel, int64_t n) {

	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot,
	                                           std::make_shared<LimitRelation>(rel->rel, n, 0));
}

[[cpp11::register]] SEXP rapi_rel_distinct(duckdb::rel_extptr_t rel) {

	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, std::make_shared<DistinctRelation>(rel->rel));
}

[[cpp11::register]] SEXP rapi_rel_to_df(duckdb::rel_extptr_t rel) {
	return result_to_df(rel->rel->Execute());
}

[[cpp11::register]] std::string rapi_rel_tostring(duckdb::rel_extptr_t rel) {
	return rel->rel->ToString();
}

[[cpp11::register]] SEXP rapi_rel_explain(duckdb::rel_extptr_t rel) {
	return result_to_df(rel->rel->Explain());
}

[[cpp11::register]] std::string rapi_rel_alias(duckdb::rel_extptr_t rel) {
	return rel->rel->GetAlias();
}

[[cpp11::register]] SEXP rapi_rel_set_alias(duckdb::rel_extptr_t rel, std::string alias) {
	cpp11::writable::list prot = {rel};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, rel->rel->Alias(alias));
}

[[cpp11::register]] SEXP rapi_rel_sql(duckdb::rel_extptr_t rel, std::string sql) {
	auto res = rel->rel->Query("_", sql);
	if (res->HasError()) {
		stop(res->GetError());
	}
	return result_to_df(std::move(res));
}

[[cpp11::register]] SEXP rapi_rel_names(duckdb::rel_extptr_t rel) {
	auto ret = writable::strings();
	for (auto &col : rel->rel->Columns()) {
		ret.push_back(col.Name());
	}
	return (ret);
}

[[cpp11::register]] SEXP rapi_rel_set_intersect(duckdb::rel_extptr_t rel_a, duckdb::rel_extptr_t rel_b) {
	auto res = std::make_shared<SetOpRelation>(rel_a->rel, rel_b->rel, SetOperationType::INTERSECT);

	cpp11::writable::list prot = {rel_a, rel_b};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_set_diff(duckdb::rel_extptr_t rel_a, duckdb::rel_extptr_t rel_b) {
	auto res = std::make_shared<SetOpRelation>(rel_a->rel, rel_b->rel, SetOperationType::EXCEPT);

	cpp11::writable::list prot = {rel_a, rel_b};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, res);
}

[[cpp11::register]] SEXP rapi_rel_set_symdiff(duckdb::rel_extptr_t rel_a, duckdb::rel_extptr_t rel_b) {
	// symdiff implemented using the equation below
	// A symdiff B = (A except B) UNION (B except A)
	auto a_except_b = std::make_shared<SetOpRelation>(rel_a->rel, rel_b->rel, SetOperationType::EXCEPT);
	auto b_except_a = std::make_shared<SetOpRelation>(rel_b->rel, rel_a->rel, SetOperationType::EXCEPT);
	auto symdiff = std::make_shared<SetOpRelation>(a_except_b, b_except_a, SetOperationType::UNION);

	cpp11::writable::list prot = {rel_a, rel_b};

	return make_external_prot<RelationWrapper>("duckdb_relation", prot, symdiff);
}
