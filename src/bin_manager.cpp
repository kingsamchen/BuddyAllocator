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
    maximum_slot_.resize(node_count - 1);
    size_t node_slot_count = total_slot_count << 1;
    for (size_t i = 0; i < node_count; ++i) {
        if (buddy_util::IsPowerOf2(i + 1)) {
            node_slot_count >>= 1;
        }

        maximum_slot_[i] = node_slot_count;
    }
}

