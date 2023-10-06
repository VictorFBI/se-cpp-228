#pragma once

template <class T>
class UniquePtr {
public:
    UniquePtr() {
        ptr_ = nullptr;
    }
    explicit UniquePtr(T* obj) {
        ptr_ = obj;
    }
    UniquePtr(UniquePtr& obj) = delete;
    UniquePtr& operator=(UniquePtr& obj) = delete;
    UniquePtr(UniquePtr&& obj) noexcept {
        ptr_ = obj.ptr_;
        obj.ptr_ = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& obj) noexcept {
        if (&obj != this) {
            delete ptr_;
            ptr_ = obj.ptr_;
            obj.ptr_ = nullptr;
        }
        return *this;
    }
    ~UniquePtr() {
        delete ptr_;
    }
    T& operator*() {
        return *ptr_;
    }
    T* operator->() {
        return ptr_;
    }
    void Reset(T* ptr = nullptr) {
        if (ptr != ptr_) {
            delete ptr_;
            ptr_ = ptr;
        }
    }

private:
    T* ptr_;
};
