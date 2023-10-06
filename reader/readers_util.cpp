#include "readers_util.h"

#include <cmath>
LimitReader::LimitReader(std::unique_ptr<Reader> reader, size_t limit) : reader_(std::move(reader)), limit_(limit) {
}
size_t LimitReader::Read(char *buf, size_t len) {
    char *tmp = new char[len];
    size_t res = reader_->Read(tmp, len);
    if (!res || !limit_) {
        delete[] tmp;
        return 0;
    }
    size_t min = std::min(limit_, res);
    for (size_t i = 0; i < min; ++i) {
        buf[i] = tmp[i];
    }
    delete[] tmp;
    return min;
}
TeeReader::TeeReader(std::vector<std::unique_ptr<Reader>> readers) : readers_(std::move(readers)) {
}
size_t TeeReader::Read(char *buf, size_t len) {
    size_t total_bytes = current_;
    size_t start_len = len;
    for (size_t i = 0; i < readers_.size(); ++i) {
        size_t res = readers_[i]->Read(buf, len);
        if (!res) {
            len = start_len;
            continue;
        }
        total_bytes += res;
        len -= res;
        buf += res;
        --i;
    }
    return total_bytes;
}
HexDecodingReader::HexDecodingReader(std::unique_ptr<Reader> reader) : reader_(std::move(reader)) {
}
size_t HexDecodingReader::Read(char *buf, size_t len) {
    int pos = 0;
    const int hex = 16;
    const int digit_difference = 48;
    const int letter_difference = 87;
    char *tmp = new char[len];
    size_t res = reader_->Read(tmp, len);
    if (!res) {
        delete[] tmp;
        return 0;
    }
    for (size_t i = 0; i < len; i = i + 2) {
        int num = 0;
        for (size_t j = i; j < i + 2; ++j) {
            if (isdigit(tmp[j])) {
                num += (static_cast<int>(tmp[j]) - digit_difference) * static_cast<int>(std::pow(hex, (j + 1) % 2));
            } else {
                num += (static_cast<int>(tmp[j]) - letter_difference) * static_cast<int>(std::pow(hex, (j + 1) % 2));
            }
        }
        buf[pos++] = static_cast<char>(num);
    }
    delete[] tmp;
    return res / 2;
}
