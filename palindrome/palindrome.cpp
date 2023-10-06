#include "palindrome.h"

bool IsPalindrome(const std::string &str) {
    size_t i = 0;
    size_t j = str.length() - 1;
    if (str.empty()) {
        return true;
    }
    while ((i - j) / 2 != 0) {
        if (str[i] == ' ') {
            ++i;
            continue;
        }
        if (str[j] == ' ') {
            --j;
            continue;
        }
        if (str[i] != str[j]) {
            return false;
        }
        ++i;
        --j;
    }

    return true;
}
