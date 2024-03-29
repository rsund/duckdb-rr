//===----------------------------------------------------------------------===//
//                         DuckDB
//
// duckdb/execution/index/art/fixed_size_allocator.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include "duckdb/common/types/validity_mask.hpp"
#include "duckdb/common/unordered_set.hpp"
#include "duckdb/storage/buffer_manager.hpp"
#include "duckdb/execution/index/art/node.hpp"

namespace duckdb {

// structs
struct BufferEntry {
	BufferEntry(const data_ptr_t &ptr, const idx_t &allocation_count) : ptr(ptr), allocation_count(allocation_count) {
	}
	data_ptr_t ptr;
	idx_t allocation_count;
};

//! The FixedSizeAllocator provides pointers to fixed-size sections of pre-allocated memory buffers.
//! The pointers are Node pointers, and the leftmost byte (serialize flag and type) must always be zero.
class FixedSizeAllocator {
public:
	//! Fixed size of the buffers
	static constexpr idx_t BUFFER_ALLOC_SIZE = Storage::BLOCK_ALLOC_SIZE;
	//! We can vacuum 10% or more of the total memory usage of the allocator
	static constexpr uint8_t VACUUM_THRESHOLD = 10;

	//! Constants for fast offset calculations in the bitmask
	static constexpr idx_t BASE[] = {0x00000000FFFFFFFF, 0x0000FFFF, 0x00FF, 0x0F, 0x3, 0x1};
	static constexpr uint8_t SHIFT[] = {32, 16, 8, 4, 2, 1};

public:
	explicit FixedSizeAllocator(const idx_t allocation_size, Allocator &allocator);
	~FixedSizeAllocator();

	//! Allocation size of one element in a buffer
	idx_t allocation_size;
	//! Total number of allocations
	idx_t total_allocations;
	//! Number of validity_t values in the bitmask
	idx_t bitmask_count;
	//! First starting byte of the payload
	idx_t allocation_offset;
	//! Number of possible allocations per buffer
	idx_t allocations_per_buffer;

	//! Buffers containing the data
	vector<BufferEntry> buffers;
	//! Buffers with free space
	unordered_set<idx_t> buffers_with_free_space;

	//! Minimum buffer ID of buffers that can be vacuumed
	idx_t min_vacuum_buffer_id;

	//! Buffer manager of the database instance
	Allocator &allocator;

public:
	//! Get a new Node pointer to data, might cause a new buffer allocation
	Node New();
	//! Free the data of the Node pointer
	void Free(const Node ptr);
	//! Get the data of the Node pointer
	template <class T>
	inline T *Get(const Node ptr) const {
		return (T *)Get(ptr);
	}

	//! Resets the allocator, e.g., becomes necessary during DELETE FROM table
	void Reset();

	//! Returns the allocated memory size in bytes
	inline idx_t GetMemoryUsage() const {
		return buffers.size() * BUFFER_ALLOC_SIZE;
	}

	//! Merge another FixedSizeAllocator into this allocator. Both must have the same allocation size
	void Merge(FixedSizeAllocator &other);

	//! Initialize a vacuum operation, and return true, if the allocator needs a vacuum
	bool InitializeVacuum();
	//! Finalize a vacuum operation by freeing all buffers exceeding the min_vacuum_buffer_id
	void FinalizeVacuum();
	//! Returns true, if a Node pointer qualifies for a vacuum operation, and false otherwise
	inline bool NeedsVacuum(const Node ptr) const {
		if (ptr.GetBufferId() >= min_vacuum_buffer_id) {
			return true;
		}
		return false;
	}
	//! Vacuums a Node pointer
	Node VacuumPointer(const Node ptr);

	//! Verify that the allocation counts match the existing positions on the buffers
	void Verify() const;

private:
	//! Returns the data_ptr_t of a Node pointer
	inline data_ptr_t Get(const Node ptr) const {
		D_ASSERT(ptr.GetBufferId() < buffers.size());
		D_ASSERT(ptr.GetOffset() < allocations_per_buffer);
		return buffers[ptr.GetBufferId()].ptr + ptr.GetOffset() * allocation_size + allocation_offset;
	}
	//! Returns the first free offset in a bitmask
	uint32_t GetOffset(ValidityMask &mask, const idx_t allocation_count);
};

} // namespace duckdb
