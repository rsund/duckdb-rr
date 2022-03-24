#include "src/optimizer/rule/case_simplification.cpp"

#include "src/optimizer/rule/comparison_simplification.cpp"

#include "src/optimizer/rule/conjunction_simplification.cpp"

#include "src/optimizer/rule/constant_folding.cpp"

#include "src/optimizer/rule/date_part_simplification.cpp"

#include "src/optimizer/rule/distributivity.cpp"

#include "src/optimizer/rule/empty_needle_removal.cpp"

#include "src/optimizer/rule/enum_comparison.cpp"

#include "src/optimizer/rule/in_clause_simplification_rule.cpp"

#include "src/optimizer/rule/like_optimizations.cpp"

#include "src/optimizer/rule/move_constants.cpp"

#include "src/optimizer/statistics/expression/propagate_aggregate.cpp"

#include "src/optimizer/statistics/expression/propagate_and_compress.cpp"

#include "src/optimizer/statistics/expression/propagate_between.cpp"

#include "src/optimizer/statistics/expression/propagate_case.cpp"

#include "src/optimizer/statistics/expression/propagate_cast.cpp"

#include "src/optimizer/statistics/expression/propagate_columnref.cpp"

#include "src/optimizer/statistics/expression/propagate_comparison.cpp"

#include "src/optimizer/statistics/expression/propagate_conjunction.cpp"

#include "src/optimizer/statistics/expression/propagate_constant.cpp"

#include "src/optimizer/statistics/expression/propagate_function.cpp"

#include "src/optimizer/statistics/expression/propagate_operator.cpp"

#include "src/optimizer/statistics/operator/propagate_aggregate.cpp"

#include "src/optimizer/statistics/operator/propagate_cross_product.cpp"

#include "src/optimizer/statistics/operator/propagate_filter.cpp"

#include "src/optimizer/statistics/operator/propagate_get.cpp"

#include "src/optimizer/statistics/operator/propagate_join.cpp"

#include "src/optimizer/statistics/operator/propagate_limit.cpp"

#include "src/optimizer/statistics/operator/propagate_order.cpp"

#include "src/optimizer/statistics/operator/propagate_projection.cpp"

#include "src/optimizer/statistics/operator/propagate_set_operation.cpp"

#include "src/optimizer/statistics/operator/propagate_window.cpp"

#include "src/optimizer/statistics_propagator.cpp"

#include "src/optimizer/topn_optimizer.cpp"

#include "src/parallel/event.cpp"

#include "src/parallel/executor.cpp"

#include "src/parallel/executor_task.cpp"

#include "src/parallel/pipeline.cpp"

#include "src/parallel/pipeline_complete_event.cpp"

#include "src/parallel/pipeline_event.cpp"

#include "src/parallel/pipeline_executor.cpp"

#include "src/parallel/pipeline_finish_event.cpp"

#include "src/parallel/task_scheduler.cpp"

#include "src/parallel/thread_context.cpp"

#include "src/parser/base_expression.cpp"

#include "src/parser/column_definition.cpp"

#include "src/parser/constraint.cpp"

#include "src/parser/constraints/check_constraint.cpp"

#include "src/parser/constraints/foreign_key_constraint.cpp"

