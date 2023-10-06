#pragma once

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    for (T i = begin; i != end; ++i) {
        if (*i != value) {
            *begin = *i;
            begin++;
        }
    }
    return begin;
}
