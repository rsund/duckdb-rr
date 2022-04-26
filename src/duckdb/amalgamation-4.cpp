#include "src/execution/operator/helper/physical_load.cpp"

#include "src/execution/operator/helper/physical_pragma.cpp"

#include "src/execution/operator/helper/physical_prepare.cpp"

#include "src/execution/operator/helper/physical_reservoir_sample.cpp"

#include "src/execution/operator/helper/physical_set.cpp"

#include "src/execution/operator/helper/physical_streaming_sample.cpp"

#include "src/execution/operator/helper/physical_transaction.cpp"

#include "src/execution/operator/helper/physical_vacuum.cpp"

#include "src/execution/operator/join/perfect_hash_join_executor.cpp"

#include "src/execution/operator/join/physical_blockwise_nl_join.cpp"

#include "src/execution/operator/join/physical_comparison_join.cpp"

#include "src/execution/operator/join/physical_cross_product.cpp"

#include "src/execution/operator/join/physical_delim_join.cpp"

#include "src/execution/operator/join/physical_hash_join.cpp"

#include "src/execution/operator/join/physical_iejoin.cpp"

#include "src/execution/operator/join/physical_index_join.cpp"

#include "src/execution/operator/join/physical_join.cpp"

#include "src/execution/operator/join/physical_nested_loop_join.cpp"

#include "src/execution/operator/join/physical_piecewise_merge_join.cpp"

#include "src/execution/operator/join/physical_range_join.cpp"

#include "src/execution/operator/order/physical_order.cpp"

#include "src/execution/operator/order/physical_top_n.cpp"

#include "src/execution/operator/persistent/buffered_csv_reader.cpp"

#include "src/execution/operator/persistent/physical_copy_to_file.cpp"

#include "src/execution/operator/persistent/physical_delete.cpp"

#include "src/execution/operator/persistent/physical_export.cpp"

#include "src/execution/operator/persistent/physical_insert.cpp"

#include "src/execution/operator/persistent/physical_update.cpp"

#include "src/execution/operator/projection/physical_projection.cpp"

#include "src/execution/operator/projection/physical_tableinout_function.cpp"

#include "src/execution/operator/projection/physical_unnest.cpp"

#include "src/execution/operator/scan/physical_chunk_scan.cpp"

#include "src/execution/operator/scan/physical_dummy_scan.cpp"

#include "src/execution/operator/scan/physical_empty_result.cpp"

#include "src/execution/operator/scan/physical_expression_scan.cpp"

#include "src/execution/operator/scan/physical_table_scan.cpp"

#include "src/execution/operator/schema/physical_alter.cpp"

#include "src/execution/operator/schema/physical_create_function.cpp"

#include "src/execution/operator/schema/physical_create_index.cpp"

#include "src/execution/operator/schema/physical_create_schema.cpp"

#include "src/execution/operator/schema/physical_create_sequence.cpp"

#include "src/execution/operator/schema/physical_create_table.cpp"

#include "src/execution/operator/schema/physical_create_table_as.cpp"

#include "src/execution/operator/schema/physical_create_type.cpp"

#include "src/execution/operator/schema/physical_create_view.cpp"

#include "src/execution/operator/schema/physical_drop.cpp"

#include "src/execution/operator/set/physical_recursive_cte.cpp"

#include "src/execution/operator/set/physical_union.cpp"

#include "src/execution/partitionable_hashtable.cpp"

