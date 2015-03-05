/*
 @ Kingsley Chen
*/

#include "buddy_allocator.h"

#include "kbase\error_exception_util.h"

namespace {

size_t BytesToSlots(size_t size_in_bytes)
{
    ENSURE(size_in_bytes % BuddyAllocator::granularity() == 0)(size_in_bytes).raise();
    return size_in_bytes / BuddyAllocator::granularity();
}

}   // namespace

// static
size_t BuddyAllocator::granularity()
{
    using SlotType = decltype(memory_bin_);
    return SlotType::slot_granularity;
}

BuddyAllocator::BuddyAllocator(size_type max_byte /* = DEFAULT_CAPACITY */)
    : bin_manager_(BytesToSlots(max_byte)),
      memory_bin_(BytesToSlots(max_byte)),
      capacity_(max_byte)
{}
