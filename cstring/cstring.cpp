#include "cstring.h"
size_t Strlen(const char *str) {
    if (!str) {
        return 0;
    }
    size_t result = 0;
    while (*(str + result) != '\0') {
        ++result;
    }
    return result;
}
int Strcmp(const char *first, const char *second) {
    size_t first_size = Strlen(first);
    size_t second_size = Strlen(second);
    size_t min = std::min(first_size, second_size);
    for (size_t i = 0; i < min; ++i) {
        if (first[i] < second[i]) {
            return -1;
        }
        if (first[i] > second[i]) {
            return 1;
        }
    }
    if (first_size < second_size) {
        return -1;
    }
    if (first_size > second_size) {
        return 1;
    }
    return 0;
}
int Strncmp(const char *first, const char *second, size_t count) {
    size_t first_size = Strlen(first);
    size_t second_size = Strlen(second);
    size_t min_size = std::min(first_size, second_size);
    size_t min = std::min(min_size, count);
    for (size_t i = 0; i < min; ++i) {
        if (first[i] < second[i]) {
            return -1;
        }
        if (first[i] > second[i]) {
            return 1;
        }
    }
    if (min == count) {
        return 0;
    }
    if (first_size < second_size) {
        return -1;
    }
    if (first_size > second_size) {
        return 1;
    }
    return 0;
}
char *Strcpy(char *dest, const char *src) {
    size_t src_size = Strlen(src);
    for (size_t i = 0; i <= src_size; ++i) {
        dest[i] = src[i];
    }
    return dest;
}
char *Strncpy(char *dest, const char *src, size_t count) {
    size_t src_size = Strlen(src);
    if (count <= src_size) {
        for (size_t i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i = 0; i < src_size; ++i) {
            dest[i] = src[i];
        }
        for (size_t i = 0; i < count; ++i) {
            dest[src_size + i] = '\0';
        }
    }

    return dest;
}
char *Strcat(char *dest, const char *src) {
    size_t src_size = Strlen(src);
    size_t dest_size = Strlen(dest);
    for (size_t i = 0; i < src_size; ++i) {
        dest[dest_size + i] = src[i];
    }
    return dest;
}
char *Strncat(char *dest, const char *src, size_t count) {
    size_t src_size = Strlen(src);
    size_t dest_size = Strlen(dest);
    if (count > src_size) {
        for (size_t i = 0; i < src_size; ++i) {
            dest[dest_size + i] = src[i];
        }
    } else {
        for (size_t i = 0; i < count; ++i) {
            dest[dest_size + i] = src[i];
        }
    }
    return dest;
}
const char *Strchr(const char *str, char symbol) {
    size_t str_size = Strlen(str);
    for (size_t i = 0; i <= str_size; ++i) {
        if (str[i] == symbol) {
            return str + i;
        }
    }
    return nullptr;
}
const char *Strrchr(const char *str, char symbol) {
    size_t str_size = Strlen(str);
    for (size_t i = str_size; i != 0; --i) {
        if (str[i] == symbol) {
            return str + i;
        }
    }
    if (str[0] == symbol) {
        return str;
    }
    return nullptr;
}
size_t Strspn(const char *dest, const char *src) {
    size_t src_size = Strlen(src);
    size_t dest_size = Strlen(dest);
    size_t prev_res = 0;
    size_t res = 0;
    for (size_t i = 0; i < dest_size; ++i) {
        for (size_t j = 0; j < src_size; ++j) {
            prev_res = res;
            if (dest[i] == src[j]) {
                ++res;
                break;
            }
        }
        if (prev_res == res) {
            break;
        }
    }
    return res;
}
size_t Strcspn(const char *dest, const char *src) {
    size_t src_size = Strlen(src);
    size_t dest_size = Strlen(dest);
    size_t idx = 0;
    size_t count = 0;
    if (!src_size) {
        return dest_size;
    }
    for (size_t i = 0; i < dest_size; ++i) {
        for (size_t j = 0; j < src_size; ++j) {
            if (dest[i] == src[j]) {
                ++count;
                idx = i;
                break;
            }
        }
        if (count == 1) {
            break;
        }
    }
    return count == 0 ? dest_size : idx;
}
const char *Strpbrk(const char *dest, const char *breakset) {
    size_t breakset_size = Strlen(breakset);
    size_t dest_size = Strlen(dest);
    for (size_t i = 0; i < dest_size; ++i) {
        for (size_t j = 0; j < breakset_size; ++j) {
            if (dest[i] == breakset[j]) {
                return dest + i;
            }
        }
    }
    return nullptr;
}
const char *Strstr(const char *str, const char *pattern) {
    size_t pattern_size = Strlen(pattern);
    size_t str_size = Strlen(str);
    if (pattern_size > str_size) {
        return nullptr;
    }
    if (pattern_size == 0) {
        return str;
    }
    for (size_t i = 0; i < str_size - pattern_size + 1; ++i) {
        if (str[i] == pattern[0]) {
            size_t tmp = i + 1;
            size_t size = 1;
            for (size_t j = 1; j < pattern_size; ++j) {
                if (str[tmp] == pattern[j]) {
                    ++size;
                }
                ++tmp;
            }
            if (size == pattern_size) {
                return str + i;
            }
        }
    }
    return nullptr;
}