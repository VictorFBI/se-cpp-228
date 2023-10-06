#pragma once

template <typename T>
bool IsEqual(T first, T second) {
    return !(*first < *second) && !(*second < *first);
}

template <typename T>
T IsSortedUntil(T begin, T end) {
    for (T i = begin; i != end; ++i) {
        if (!(*i < *(i + 1)) && !IsEqual(i, i + 1)) {
            return i + 1;
        }
    }

    return end;
}
