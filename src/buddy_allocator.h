/*
 @ Kingsley Chen
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BUDDY_ALLOCATOR_H_
#define BUDDY_ALLOCATOR_H_

class BuddyAllocator {
public:
    using size_type = size_t;
    using pointer = void*;

    BuddyAllocator();

    BuddyAllocator(const BuddyAllocator&) = delete;

    BuddyAllocator& operator=(const BuddyAllocator&) = delete;

    ~BuddyAllocator();

    pointer Allocate(size_type number_of_bytes);

    void Deallocate(pointer ptr);
};

#endif  // BUDDY_ALLOCATOR_H_