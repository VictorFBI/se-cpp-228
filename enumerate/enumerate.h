#pragma once
#include <functional>
#include <utility>
template <class Iterator>
class IteratorRange {
public:
    IteratorRange(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }

    Iterator begin() const {  // NOLINT
        return begin_;
    }

    Iterator end() const {  // NOLINT
        return end_;
    }

public:
    Iterator begin_, end_;
};

template <class T>
class EnumerateIterator {
public:
    explicit EnumerateIterator(T ptr) : ptr_(ptr), idx_(0) {
    }
    auto operator!=(EnumerateIterator other) {
        return ptr_ != other.ptr_;
    }
    auto operator++() {
        ++ptr_;
        ++idx_;
        return *this;
    }
    auto operator*() {
        return std::make_pair(idx_, std::ref(*ptr_));
    }

public:
    T ptr_;
    int idx_;
};

template <typename Container>
auto Enumerate(Container& cont) {
    return IteratorRange(EnumerateIterator(cont.begin()), EnumerateIterator(cont.end()));
}
