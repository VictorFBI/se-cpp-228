#include <algorithm>

#pragma once

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    --end;
    Iterator i = begin;
    Iterator j = end;
    for (; j - i >= 1; ++i, --j) {
        std::swap(*i, *j);
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    if (begin == mid) {
        return;
    }
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}