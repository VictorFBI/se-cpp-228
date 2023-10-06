#include "password.h"

#include <cctype>

bool ValidatePassword(const std::string& password) {
    bool lower_flag = false;
    bool upper_flag = false;
    bool digit_flag = false;
    bool other_flag = false;
    const int upper_bound_char = 126;
    const int lower_bound_char = 33;
    const int upper_bound_length = 14;
    const int lower_bound_length = 8;

    for (size_t i = 0; i < password.length(); ++i) {
        if (password[i] > upper_bound_char || password[i] < lower_bound_char) {
            return false;
        }
    }
    if (password.length() > upper_bound_length || password.length() < lower_bound_length) {
        return false;
    }
    for (size_t i = 0; i < password.length(); ++i) {
        if (std::islower(password[i])) {
            lower_flag = true;
            continue;
        }
        if (std::isupper(password[i])) {
            upper_flag = true;
            continue;
        }
        if (std::isdigit(password[i])) {
            digit_flag = true;
            continue;
        }
        other_flag = true;
    }

    return lower_flag + upper_flag + digit_flag + other_flag >= 3;
}
