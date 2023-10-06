#include "factorization.h"

bool IsPrime(const int64_t& x) {
    for (int64_t i = 2; i * i <= x; ++i) {
        if (x % i == 0) {
            return false;
        }
    }

    return true;
}

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> vec;

    if (IsPrime(x)) {
        vec.emplace_back(x, 1);
        return vec;
    }

    for (int64_t i = 2; i <= x / 2; ++i) {
        if (x % i == 0 && IsPrime(i)) {
            int k = 0;
            while (x % i == 0) {
                ++k;
                x /= i;
            }
            vec.emplace_back(i, k);
            i = 2;
        }
    }

    if (x != 1) {
        vec.emplace_back(x, 1);
    }

    return vec;
}
