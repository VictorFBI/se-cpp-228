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

private:
    Iterator begin_, end_;
};
class RangeIterator {
public:
    explicit RangeIterator(int64_t num, int64_t step) : num_(num), step_(step) {
    }
    auto operator!=(RangeIterator other) const {
        return num_ <= other.num_;
    }
    auto operator*() const {
        return num_;
    }
    auto operator++() {
        num_ += step_;
        return *this;
    }

private:
    int64_t num_;
    int64_t step_;
};
inline auto Range(int64_t from, int64_t to, int64_t step = 1) {
    return IteratorRange(RangeIterator(from, step), RangeIterator(to, step));
}
inline auto Range(int64_t number) {
    return Range(0, number - 1);
}

template <typename U, typename V>
class ZipIterator {
public:
    ZipIterator(U first, V second) : first_(first), second_(second) {
    }
    auto operator!=(ZipIterator other) {
        return (first_ != other.first_) && (second_ != other.second_);
    }
    auto operator*() {
        return std::make_pair((*first_), (*second_));
    }
    auto operator++() {
        ++first_;
        ++second_;
        return *this;
    }

private:
    U first_;
    V second_;
};
template <typename Container1, typename Container2>
auto Zip(Container1&& cont1, Container2&& cont2) {
    auto begin1 = cont1.begin();
    auto begin2 = cont2.begin();
    auto end1 = begin1;
    auto end2 = begin2;
    while (end1 != cont1.end() && end2 != cont2.end()) {
        ++end1;
        ++end2;
    }
    return IteratorRange(ZipIterator(begin1, begin2), ZipIterator(end1, end2));
}

template <class Iterator>
class GroupIterator {
public:
    GroupIterator(Iterator begin, Iterator end) : begin_(begin), end_(end) {
    }
    auto operator*() {
        Iterator new_end = begin_;
        while (new_end != end_ && *new_end == *begin_) {
            ++new_end;
        }
        return IteratorRange(begin_, new_end);
    }

    auto operator!=(GroupIterator other) {
        return begin_ != other.begin_;
    }
    auto operator++() {
        Iterator begin = begin_;
        while (begin_ != end_ && *begin == *begin_) {
            ++begin_;
        }
        return *this;
    }

private:
    Iterator begin_;
    Iterator end_;
};
template <typename Container>
auto Group(Container& cont) {

    return IteratorRange(GroupIterator(cont.begin(), cont.end()), GroupIterator(cont.end(), cont.end()));
}
