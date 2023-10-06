#include "string_view.h"
StringView::StringView() {
    string_ = nullptr;
    size_ = 0;
}
StringView::StringView(const char *source) {
    string_ = source;
    size_ = 0;
    while (*source != '\0') {
        ++size_;
        ++source;
    }
}
StringView::StringView(const char *cstyle, size_t length) {
    string_ = cstyle;
    size_ = length;
}
char StringView::operator[](size_t idx) const {
    return *(string_ + idx);
}
char StringView::At(size_t idx) const {
    if (idx >= size_ || idx < 0) {
        throw StringViewOutOfRange{};
    } else {
        return *(string_ + idx);
    }
}
char StringView::Front() const {
    return this->At(0);
}
char StringView::Back() const {
    return this->At(size_ - 1);
}
size_t StringView::Size() const {
    return size_;
}
size_t StringView::Length() const {
    return size_;
}
const char *StringView::Data() const {
    return string_;
}
bool StringView::Empty() const {
    return size_ == 0;
}
void StringView::Swap(StringView &other) {
    std::swap(*this, other);
}
void StringView::RemovePrefix(size_t prefix_size) {
    if (prefix_size > size_) {
        throw StringViewOutOfRange{};
    }
    string_ += prefix_size;
    size_ -= prefix_size;
}
void StringView::RemoveSuffix(size_t suffix_size) {
    if (suffix_size > size_) {
        throw StringViewOutOfRange{};
    }
    size_ -= suffix_size;
}
StringView StringView::Substr(size_t pos, size_t count) {
    if (pos + count > size_) {
        throw StringViewOutOfRange{};
    }
    auto tmp = *this;
    tmp.RemovePrefix(pos);
    tmp.RemoveSuffix(tmp.size_ - count);
    return tmp;
}
