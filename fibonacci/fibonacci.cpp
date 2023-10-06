#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n == 0) {
        return 0;
    } else if (n <= 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return CalculateNthFibonacci(n / 2) * (2 * CalculateNthFibonacci(n / 2 + 1) - CalculateNthFibonacci(n / 2));
    } else {
        int64_t k = (n - 1) / 2;
        return CalculateNthFibonacci(k + 1) * CalculateNthFibonacci(k + 1) +
               CalculateNthFibonacci(k) * CalculateNthFibonacci(k);
    }
}