#pragma once

#include <memory>
#include <string>
#include <vector>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> res;
    for (auto& el : items) {
        res.push_back(std::make_unique<T>(*el));
    }
    return res;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> res;
    for (size_t i = 0; i < items.size(); ++i) {
        res.push_back(std::make_shared<T>(*items[i]));
        for (size_t j = 0; j < res.size(); ++j) {
            if (*items[i] == *res[j]) {
                res[res.size() - 1] = res[j];
                break;
            }
        }
    }
    return res;
}
