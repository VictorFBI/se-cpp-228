#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> vec;
    if (from == to || (from > to && step >= 0) || (from < to && step <= 0)) {
        return vec;
    }
    if (from > to) {
        do {
            vec.push_back(from);
            from += step;
        } while (from > to);
    } else {
        do {
            vec.push_back(from);
            from += step;
        } while (from < to);
    }

    return vec;
}
