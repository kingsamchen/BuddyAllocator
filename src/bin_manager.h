/*
 @ Kingsley Chen
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BIN_MANAGER_H_
#define BIN_MANAGER_H_

#include <vector>

class BinManager {
public:
    // |initial_slot_count| must be a power of 2.
    explicit BinManager(size_t total_slot_count);

    BinManager(const BinManager&) = delete;

    BinManager(BinManager&& other);

    BinManager& operator=(const BinManager&) = delete;

    BinManager& operator=(BinManager&& rhs);

    ~BinManager() = default;

    size_t Allocate(size_t slots_required);

private:
    size_t total_slot_count_;
    std::vector<size_t> maximum_slot_;
};

#endif  // BIN_MANAGER_H_