/*
 @ Kingsley Chen
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef MEMORY_BIN_H_
#define MEMORY_BIN_H_

#include <cstdint>

#include "compiler_helper.h"

template<size_t Granularity>
struct SlotTraits {
    enum { granularity = Granularity };
    uint8_t s[Granularity];
};

// Using 4K for a slot by default.
using DefaultSlotTraits = SlotTraits<4096>;

template<typename SlotTraitsType = DefaultSlotTraits>
class MemoryBin {
private:
    using Slot = SlotTraitsType;

public:
    MemoryBin(size_t slot_count) {};

    MemoryBin(const MemoryBin&) = delete;

    MemoryBin(MemoryBin&& other);

    MemoryBin& operator=(const MemoryBin&) = delete;

    MemoryBin& operator=(MemoryBin&& rhs);

    ~MemoryBin() = default;

    static size_t slot_granularity()
    {
        return Slot::granularity;
    }

private:
    FRIEND_TEST_WITH_PREFIX(MemoryBin);
};

#endif  // MEMORY_BIN_H_