#pragma once

#include <iostream>
#include <memory>

class Any {
private:
    struct InnerBase {

        virtual ~InnerBase() {
        }

        virtual InnerBase* Clone() const = 0;
    };

    template <class T>
    struct Inner : public InnerBase {

        explicit Inner(const T& val) : value_(val) {
        }

        InnerBase* Clone() const override {
            return new Inner(value_);
        }

        T value_;
    };

    InnerBase* ptr_;

public:
    Any() : ptr_(nullptr) {
    }
    template <class T>
    explicit Any(const T& value) {
        ptr_ = new Inner<T>(value);
    }

    template <class T>
    Any& operator=(const T& value) {
        delete ptr_;
        ptr_ = new Inner<T>(value);
        return *this;
    }

    Any(const Any& rhs) : ptr_(rhs.ptr_->Clone()) {
    }
    Any& operator=(Any rhs) {
        Swap(rhs);
        return *this;
    }
    ~Any() {
        delete ptr_;
    }

    bool Empty() const {
        return !ptr_;
    }

    void Clear() {
        delete ptr_;
        ptr_ = nullptr;
    }
    void Swap(Any& rhs) {
        std::swap(ptr_, rhs.ptr_);
    }

    template <class T>
    const T& GetValue() const {
        return dynamic_cast<Inner<T>&>(*ptr_).value_;
    }
};
