/*
 @ Kingsley Chen
*/

#include "bin_manager.h"

#include "kbase\error_exception_util.h"

#include "buddy_util.h"


BinManager::BinManager(size_t total_slot_count)
    : total_slot_count_(total_slot_count)
{
    ENSURE(buddy_util::IsPowerOf2(total_slot_count))(total_slot_count).raise();

    size_t node_count = (total_slot_count << 1) - 1;
    maximum_slot_.resize(node_count);
    size_t node_slot_count = total_slot_count << 1;
    for (size_t i = 0; i < node_count; ++i) {
        if (buddy_util::IsPowerOf2(i + 1)) {
            node_slot_count >>= 1;
        }

        maximum_slot_[i] = node_slot_count;
    }
}

size_t BinManager::Allocate(size_t slots_required)
{
    // if slots_required is not a power of 2, tweak it to the next.
    // if there is no bin with enough slots, return noffset.
    // traverse the bin-node-tree (left->right) to find a match.
    // backtrace to fix the current bin nodes information.
    return 0;
}