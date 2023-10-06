#include "stack.h"

Node::Node(int32_t value, Node *previous) {
    this->value = value;
    this->previous = previous;
}

Stack::Stack() {
    size_ = 0;
    head_ = nullptr;
}
Stack::~Stack() {
    while (head_ != nullptr) {
        auto previous = head_->previous;
        delete head_;
        head_ = previous;
    }
    delete head_;
}
void Stack::Push(int32_t value) {
    ++size_;
    head_ = new Node(value, head_);
}
void Stack::Pop() {
    --size_;
    auto previous = head_->previous;
    delete head_;
    head_ = previous;
}
int32_t Stack::Top() const {
    return head_->value;
}
int32_t Stack::Size() const {
    return size_;
}
void Stack::Clear() {
    while (head_ != nullptr) {
        auto previous = head_->previous;
        delete head_;
        head_ = previous;
    }
    size_ = 0;
}
bool Stack::Empty() const {
    if (size_ == 0) {
        return true;
    }

    return false;
}
