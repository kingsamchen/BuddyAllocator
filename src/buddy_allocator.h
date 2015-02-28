
#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BUDDY_ALLOCATOR_H_
#define BUDDY_ALLOCATOR_H_

class BuddyAllocator {
public:
    BuddyAllocator();
    ~BuddyAllocator();
};

#endif  // BUDDY_ALLOCATOR_H_