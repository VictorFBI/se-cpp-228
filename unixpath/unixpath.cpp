#include "unixpath.h"

std::string GetAnswer(std::vector<std::string_view> vec) {
    if (vec.empty()) {
        return "/";
    }
    std::string ans;
    for (auto &el : vec) {
        ans += "/";
        ans += el;
    }
    return ans;
}

void CleanForwardSlashes(std::string_view &str) {
    size_t slash_count = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '/') {
            ++slash_count;
        } else {
            break;
        }
    }
    str.remove_prefix(slash_count);
}

void CleanBackwardSlashes(std::string_view &str) {
    size_t slash_count = 0;
    for (size_t i = str.size() - 1; i != 0; --i) {
        if (str[i] == '/') {
            ++slash_count;
        } else {
            break;
        }
    }
    str.remove_suffix(slash_count);
}

std::vector<std::string_view> Split(std::string_view str) {
    std::vector<std::string_view> ans;
    while (!str.empty()) {
        if (str[0] == '/') {
            CleanForwardSlashes(str);
        } else {
            size_t size = 0;
            for (size_t i = 0; i < str.size(); ++i) {
                if (str[i] != '/') {
                    ++size;
                } else {
                    break;
                }
            }
            ans.push_back(str.substr(0, size));
            str.remove_prefix(size);
        }
    }

    return ans;
}
size_t SlashCount(std::string_view str) {
    size_t slash_count = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '/') {
            ++slash_count;
        }
    }

    return slash_count;
}
std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string ans;
    std::vector<std::string_view> vec;
    if (path[0] == '/') {
        if (SlashCount(path) == path.size()) {
            return "/";
        }
        CleanForwardSlashes(path);
        CleanBackwardSlashes(path);
        ans += "/";
        ans += path;
        return ans;
    } else {
        vec = Split(current_working_dir);
        while (!path.empty()) {
            if (path.starts_with("..")) {
                if (!vec.empty()) {
                    vec.pop_back();
                }
                path.remove_prefix(2);
                continue;
            }
            if (path.starts_with(".") || path.starts_with("/")) {
                path.remove_prefix(1);
                continue;
            }
            size_t size = 0;
            for (size_t i = 0; i < path.size(); ++i) {
                if (path[i] == '/') {
                    break;
                } else {
                    ++size;
                }
            }
            vec.push_back(path.substr(0, size));
            path.remove_prefix(size);
        }
        return GetAnswer(vec);
    }
}
