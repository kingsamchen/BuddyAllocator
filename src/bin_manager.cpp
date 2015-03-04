/*
 @ Kingsley Chen
*/

#include "bin_manager.h"

#include <algorithm>

#if defined(UNITTEST_ENABLED)
#define NDEBUG
#include "kbase\error_exception_util.h"
#undef NDEBUG
#else
#include "kbase\error_exception_util.h"
#endif

#include "buddy_util.h"


BinManager::BinManager(size_t total_slot_count)
    : total_slot_count_(total_slot_count)
{
    ENSURE(buddy_util::IsPowerOf2(total_slot_count))(total_slot_count).raise();

    size_t node_count = (total_slot_count << 1) - 1;
    max_consecutive_slot_.resize(node_count);
    size_t node_slot_count = total_slot_count << 1;
    for (size_t i = 0; i < node_count; ++i) {
        if (buddy_util::IsPowerOf2(i + 1)) {
            node_slot_count >>= 1;
        }

        max_consecutive_slot_[i] = node_slot_count;
    }
}

size_t BinManager::Allocate(size_t slots_required)
{
    assert(slots_required != 0);
    if (slots_required == 0) {
        return BinManager::noffset;
    }

    size_t slots_needed = buddy_util::NearestUpperPowerOf2(slots_required);
    if (max_consecutive_slot_[0] < slots_needed) {
        return BinManager::noffset;
    }

    size_t index = 0;
    for (; max_consecutive_slot_[index] != slots_needed;) {
        if (max_consecutive_slot_[buddy_util::LeftChild(index)] >= slots_needed) {
            index = buddy_util::LeftChild(index);
        } else {
            index = buddy_util::RightChild(index);
        }
    }

    max_consecutive_slot_[index] = 0;
    size_t offset = (index + 1) * slots_needed - total_slot_count_;

    while (index) {
        index = buddy_util::Parent(index);
        max_consecutive_slot_[index] = std::max(
            max_consecutive_slot_[buddy_util::LeftChild(index)],
            max_consecutive_slot_[buddy_util::RightChild(index)]);
    }

    return offset;
}