/*
 @ Kingsley Chen
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BUDDY_UTIL_H_
#define BUDDY_UTIL_H_

namespace buddy_util {

inline bool IsPowerOf2(size_t number)
{
    return number && !(number & (number - 1));
}

}   // namespace buddy_util

#endif  // BUDDY_UTIL_H_