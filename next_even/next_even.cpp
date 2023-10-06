#include "next_even.h"

int64_t NextEven(int64_t n) {
    if (static_cast<int64_t>(n) % 2 == 0) {
        return static_cast<int64_t>(n) + 2;
    } else {
        return static_cast<int64_t>(n) + 1;
    }
}
