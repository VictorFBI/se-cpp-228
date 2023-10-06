#pragma once

#include <string>
#include <string_view>
#include <vector>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path);
std::string GetAnswer(std::vector<std::string_view> vec);
void CleanForwardSlashes(std::string_view &str);
void CleanBackwardSlashes(std::string_view &str);
size_t SlashCount(std::string_view str);
std::vector<std::string_view> Split(std::string_view str);
