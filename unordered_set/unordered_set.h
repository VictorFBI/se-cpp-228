#pragma once

#include <functional>
#include <list>
#include <vector>

template <typename KeyT>
class UnorderedSet {
public:
    UnorderedSet() : n_elements_(0), data_() {
    }
    explicit UnorderedSet(size_t count) : UnorderedSet() {
        for (size_t i = 0; i < count; ++i) {
            data_.push_back(std::list<KeyT>());
        }
    }
    template <typename IteratorType,
              typename = std::enable_if_t<std::is_base_of_v<
                  std::forward_iterator_tag, typename std::iterator_traits<IteratorType>::iterator_category>>>
    UnorderedSet(IteratorType first, IteratorType last) : UnorderedSet() {
        for (IteratorType it = first; it != last; ++it) {
            Insert(*it);
        }
    }
    UnorderedSet(const UnorderedSet& other) : n_elements_(other.n_elements_), data_(other.data_) {
    }
    UnorderedSet(UnorderedSet&& other) : n_elements_(other.n_elements_), data_(std::move(other.data_)) {
        other.n_elements_ = 0;
    }
    ~UnorderedSet() = default;
    UnorderedSet& operator=(const UnorderedSet& other) {
        if (this != &other) {
            n_elements_ = other.n_elements_;
            data_ = other.data_;
        }
        return *this;
    }
    UnorderedSet& operator=(UnorderedSet&& other) noexcept {
        if (this != &other) {
            n_elements_ = other.n_elements_;
            data_ = std::move(other.data_);
            other.n_elements_ = 0;
        }
        return *this;
    }
    size_t Size() const {
        return n_elements_;
    }
    bool Empty() const {
        return Size() == 0;
    }
    void Clear() {
        for (auto& list : data_) {
            list.clear();
        }
        n_elements_ = 0;
    }

    void Insert(const KeyT& key) {
        if (BucketCount() == 0) {
            data_.push_back(std::list<KeyT>());
        }
        if (LoadFactor() == 1) {
            Rehash(2 * BucketCount());
        }
        data_[Bucket(key)].push_back(key);
        ++n_elements_;
    }
    void Insert(KeyT&& key) {
        if (BucketCount() == 0) {
            data_.push_back(std::list<KeyT>());
        }
        if (LoadFactor() == 1) {
            Rehash(2 * BucketCount());
        }
        data_[Bucket(key)].push_back(std::move(key));
        ++n_elements_;
    }
    void Erase(const KeyT& key) {
        for (auto it = data_[Bucket(key)].begin(); it != data_[Bucket(key)].end(); ++it) {
            if (*it == key) {
                data_[Bucket(key)].erase(it);
                --n_elements_;
                return;
            }
        }
    }
    bool Find(const KeyT& key) const {
        if (BucketCount() == 0) {
            return false;
        }
        for (auto& el : data_[Bucket(key)]) {
            if (el == key) {
                return true;
            }
        }
        return false;
    }
    void Rehash(size_t new_bucket_count) {
        if (new_bucket_count < Size()) {
            return;
        }
        std::vector<KeyT> vec;
        for (auto& list : data_) {
            for (auto& el : list) {
                vec.push_back(el);
            }
        }
        Clear();
        data_.clear();
        new_bucket_count = Size() == 0 ? new_bucket_count : std::min(new_bucket_count, Size());
        for (size_t i = 0; i < new_bucket_count; ++i) {
            data_.push_back(std::list<KeyT>());
        }
        for (auto& el : vec) {
            size_t idx = std::hash<KeyT>{}(el) % BucketCount();
            data_[idx].push_back(el);
            ++n_elements_;
        }
    }
    void Reserve(size_t new_bucket_count) {
        if (new_bucket_count <= BucketCount()) {
            return;
        }
        Rehash(new_bucket_count);
    }
    size_t BucketCount() const {
        return data_.size();
    }
    size_t BucketSize(size_t id) const {
        if (id >= BucketCount()) {
            return 0;
        }
        return data_[id].size();
    }
    size_t Bucket(const KeyT& key) const {
        return BucketCount() == 0 ? 0 : std::hash<KeyT>{}(key) % BucketCount();
    }
    double LoadFactor() const {
        return BucketCount() == 0 ? 0 : static_cast<double>(n_elements_) / BucketCount();
    }

private:
    size_t n_elements_;
    std::vector<std::list<KeyT>> data_;
};
