#include "word2vec.h"

#include <vector>

int ScalarProduct(const std::vector<int>& first, const std::vector<int>& second) {
    int sum = 0;
    for (size_t i = 0; i < first.size(); ++i) {
        sum += first[i] * second[i];
    }
    return sum;
}

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (words.empty() || words.size() == 1) {
        return std::vector<std::string>();
    }
    int max = ScalarProduct(vectors[0], vectors[1]);
    std::vector<std::string> closest_words;
    for (size_t i = 1; i < vectors.size(); ++i) {
        int scalar_product = ScalarProduct(vectors[0], vectors[i]);
        if (scalar_product > max) {
            max = scalar_product;
            closest_words.clear();
        }
        if (scalar_product == max) {
            closest_words.push_back(words[i]);
        }
    }

    return closest_words;
}
