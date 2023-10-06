#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> heap;
    for (auto& el : provinces) {
        heap.push(el);
    }
    int64_t passports = 0;
    while (heap.size() > 1) {
        int64_t a = heap.top();
        heap.pop();
        int64_t b = heap.top();
        heap.pop();
        passports += a + b;
        heap.push(a + b);
    }

    return passports;
}
