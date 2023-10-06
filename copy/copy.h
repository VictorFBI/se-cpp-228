#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    for (auto i = src_begin; i != src_end; ++i) {
        *dest = *i;
        ++dest;
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    --dest;
    for (auto i = src_end - 1; i >= src_begin; --i) {
        *dest = *i;
        --dest;
    }
    ++dest;
    return dest;
}