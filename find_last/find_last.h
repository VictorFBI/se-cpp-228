#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator temporary = last;
    for (auto iter = first; iter != last; ++iter) {
        if (*iter == val) {
            temporary = iter;
        }
    }
    return temporary;
}
