#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
    std::string decipher(cipher.length(), ' ');
    const int alphabet_length = 26;
    const int code_for_a_symbol = 97;
    const int code_for_z_symbol = 122;
    const int code_for_capital_a_symbol = 65;
    const int code_for_capital_z_symbol = 90;
    shift %= alphabet_length;
    for (size_t i = 0; i < cipher.length(); ++i) {
        if (cipher[i] >= code_for_a_symbol && cipher[i] <= code_for_z_symbol && cipher[i] - shift < code_for_a_symbol) {
            decipher[i] = static_cast<char>(cipher[i] + alphabet_length - shift);
            continue;
        }
        if (cipher[i] >= code_for_capital_a_symbol && cipher[i] <= code_for_capital_z_symbol &&
            cipher[i] - shift < code_for_capital_a_symbol) {
            decipher[i] = static_cast<char>(cipher[i] + alphabet_length - shift);
            continue;
        }
        decipher[i] = static_cast<char>(cipher[i] - shift);
    }

    return decipher;
}
