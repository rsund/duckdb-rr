#include "duckdb/planner/operator/logical_delim_get.hpp"

#include "duckdb/common/field_writer.hpp"
#include "duckdb/main/config.hpp"

namespace duckdb {

void LogicalDelimGet::Serialize(FieldWriter &writer) const {
	writer.WriteField(table_index);
	writer.WriteRegularSerializableList(chunk_types);
}

unique_ptr<LogicalOperator> LogicalDelimGet::Deserialize(LogicalDeserializationState &state, FieldReader &reader) {
	auto table_index = reader.ReadRequired<idx_t>();
	auto chunk_types = reader.ReadRequiredSerializableList<LogicalType, LogicalType>();
	return make_uniq<LogicalDelimGet>(table_index, chunk_types);
}

vector<idx_t> LogicalDelimGet::GetTableIndex() const {
	return vector<idx_t> {table_index};
}

string LogicalDelimGet::GetName() const {
#ifdef DEBUG
	if (DBConfigOptions::debug_print_bindings) {
		return LogicalOperator::GetName() + StringUtil::Format(" #%llu", table_index);
	}
#endif
	return LogicalOperator::GetName();
}

} // namespace duckdb
