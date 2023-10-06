#pragma once

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return end;
    }
    auto prev = *begin;
    *begin = prev;
    ++begin;
    for (auto i = begin; i != end; ++i) {
        if (*i != prev) {
            *begin = *i;
            prev = *i;
            ++begin;
        }
    }

    return begin;
}