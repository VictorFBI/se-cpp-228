#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (auto i = begin; i < end - 1; ++i) {
        for (auto j = i + 1; j < end; ++j) {
            if (!comparator(*i, *j)) {
                std::swap(*i, *j);
            }
        }
    }
}
