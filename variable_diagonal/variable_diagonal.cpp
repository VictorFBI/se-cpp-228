#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** table = new int*[lines];
    for (size_t i = 0; i < lines; ++i) {
        table[i] = new int[columns];
    }
    int number = 0;
    for (size_t i = 0; i < columns; ++i) {
        size_t lin = 0;
        size_t col = i;
        while (col != 0) {
            table[lin][col] = number++;
            ++lin;
            --col;
        }
        table[lin][col] = number++;
    }
    for (size_t i = 1; i < lines; ++i) {
        size_t lin = i;
        size_t col = columns - 1;
        while (lin < lines) {
            table[lin][col] = number++;
            ++lin;
            --col;
        }
    }

    return table;
}