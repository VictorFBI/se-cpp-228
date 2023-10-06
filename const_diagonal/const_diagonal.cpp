#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    int number = 0;
    for (int i = 0; i < COLUMNS; ++i) {
        int lin = 0;
        int col = i;
        while (col >= 0) {
            table[lin][col] = number++;
            ++lin;
            --col;
        }
    }
    for (int i = 1; i < LINES; ++i) {
        int lin = i;
        int col = COLUMNS - 1;
        while (lin < LINES) {
            table[lin][col] = number++;
            ++lin;
            --col;
        }
    }
}
