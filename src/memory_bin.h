/*
 @ Kingsley Chen
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MEMORY_BIN_H_
#define MEMORY_BIN_H_

#include <cstdint>
#include <memory>

#include "compiler_helper.h"

template<typename BlockType, size_t Granularity>
struct SlotTraits {
    enum {
        granularity = Granularity,
        block_count = granularity / sizeof(BlockType)
    };

    BlockType s[block_count];
};

// Using 4K for a slot by default.
using DefaultSlotTraits = SlotTraits<uint8_t, 4096>;

template<typename SlotTraitsType = DefaultSlotTraits>
class MemoryBin {
private:
    using Slot = SlotTraitsType;

public:
    MemoryBin(size_t slot_count)
        : slots_(std::make_unique<Slot[]>(slot_count))
    {}

    MemoryBin(const MemoryBin&) = delete;

    MemoryBin(MemoryBin&& other);

    MemoryBin& operator=(const MemoryBin&) = delete;

    MemoryBin& operator=(MemoryBin&& rhs);

    ~MemoryBin() = default;

    Slot* Map(size_t index);

    size_t slot_granularity() const
    {
        return Slot::granularity;
    }

private:
    FRIEND_TEST_WITH_PREFIX(MemoryBin);

private:
    std::unique_ptr<Slot[]> slots_;
};

#endif  // MEMORY_BIN_H_