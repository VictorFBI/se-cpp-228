#pragma once
#include <algorithm>
#include <cstddef>
template <typename T>
class List {
private:
    struct ListNode {
        explicit ListNode(ListNode* prev = nullptr, ListNode* next = nullptr) : prev(prev), next(next) {
        }
        ListNode* prev;
        ListNode* next;
        virtual ~ListNode() {
        }
    };
    struct ListNodeWithValue : public ListNode {
        explicit ListNodeWithValue(const T& value, ListNode* prev, ListNode* next)
            : ListNode(prev, next), value(value) {
        }
        explicit ListNodeWithValue(T&& value, ListNode* prev, ListNode* next)
            : ListNode(prev, next), value(std::move(value)) {
        }
        T value;
    };

    ListNode* fictive_element_;
    std::size_t size_ = 0;

    void LinkAfter(ListNode* new_element, ListNode* target) {
        new_element->prev = target;
        new_element->next = target->next;
        new_element->next->prev = new_element;
        target->next = new_element;
        ++size_;
    }
    void Unlink(ListNode* to_delete) {
        auto prev = to_delete->prev;
        auto next = to_delete->next;
        delete to_delete;
        prev->next = next;
        next->prev = prev;
        --size_;
    }
    class Iterator {
    public:
        explicit Iterator(ListNode* ptr) : ptr_(ptr) {
        }
        Iterator& operator++() {
            ptr_ = ptr_->next;
            return *this;
        }
        Iterator operator++(int) {
            auto tmp = *this;
            ptr_ = ptr_->next;
            return tmp;
        }

        Iterator& operator--() {
            ptr_ = ptr_->prev;
            return *this;
        }

        Iterator operator--(int) {
            auto tmp = *this;
            ptr_ = ptr_->prev;
            return tmp;
        }

        auto operator*() const {
            return static_cast<ListNodeWithValue*>(ptr_)->value;
        }
        auto operator->() const {
            return ptr_;
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_ == rhs.ptr_;
        }
        bool operator!=(const Iterator& rhs) const {
            return ptr_ != rhs.ptr_;
        }

    private:
        ListNode* ptr_;
    };

public:
    List() : fictive_element_(new ListNode()), size_(0) {
        fictive_element_->next = fictive_element_;
        fictive_element_->prev = fictive_element_;
    }
    List(const List& list) : List() {
        for (auto elem : list) {
            PushBack(elem);
        }
    }
    List(List&& list) : fictive_element_(list.fictive_element_), size_(list.size_) {
        list.size_ = 0;
        list.fictive_element_ = nullptr;
    }
    ~List() {
        while (!IsEmpty()) {
            PopBack();
        }
        delete fictive_element_;
    }

    List& operator=(const List& list) {
        if (this != &list) {
            while (!IsEmpty()) {
                PopBack();
            }
            size_ = 0;
            for (auto elem : list) {
                PushBack(elem);
            }
        }
        return *this;
    }
    List& operator=(List&& list) noexcept {
        if (this != &list) {
            while (!IsEmpty()) {
                PopBack();
            }
            delete fictive_element_;
            fictive_element_ = list.fictive_element_;
            size_ = list.size_;
            list.fictive_element_ = nullptr;
            list.size_ = 0;
        }
        return *this;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }
    size_t Size() const {
        return size_;
    }

    void PushBack(const T& elem) {
        ListNode* new_element = new ListNodeWithValue(elem, nullptr, nullptr);
        LinkAfter(new_element, fictive_element_->prev);
    }
    void PushBack(T&& elem) {
        ListNode* new_element = new ListNodeWithValue(std::move(elem), nullptr, nullptr);
        LinkAfter(new_element, fictive_element_->prev);
    }

    void PushFront(const T& elem) {
        ListNode* new_element = new ListNodeWithValue(elem, nullptr, nullptr);
        LinkAfter(new_element, fictive_element_);
    }
    void PushFront(T&& elem) {
        ListNode* new_element = new ListNodeWithValue(std::move(elem), nullptr, nullptr);
        LinkAfter(new_element, fictive_element_);
    }

    T& Front() {
        return static_cast<ListNodeWithValue*>(fictive_element_->next)->value;
    }
    const T& Front() const {
        return static_cast<ListNodeWithValue*>(fictive_element_->next)->value;
    }
    T& Back() {
        return static_cast<ListNodeWithValue*>(fictive_element_->prev)->value;
    }
    const T& Back() const {
        return static_cast<ListNodeWithValue*>(fictive_element_->prev)->value;
    }

    void PopBack() {
        Unlink(fictive_element_->prev);
    }
    void PopFront() {
        Unlink(fictive_element_->next);
    }

    Iterator Begin() {
        return Iterator(fictive_element_->next);
    }
    Iterator End() {
        return Iterator(fictive_element_);
    }
    Iterator begin() const {  // NOLINT
        return Iterator(fictive_element_->next);
    }
    Iterator end() const {  // NOLINT
        return Iterator(fictive_element_);
    }
};

template <typename T>
typename List<T>::Iterator begin(List<T>& list) {  // NOLINT
    return list.Begin();
}

template <typename T>
typename List<T>::Iterator end(List<T>& list) {  // NOLINT
    return list.End();
}
