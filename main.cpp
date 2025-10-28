#include <cassert>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

#include "matrix.h"

int main(int argc, char **argv) {

    int dim = 2;
    // Парсим аргументы командной строки
    for (int i = 1; i < argc; ++i) {
        if (strncmp(argv[i], "--dim=", 6) == 0) {
            dim = std::stoul(argv[i] + 6);
        }
    }

    Matrix<int, 0> matrix(dim);

    if (dim == 2) {
        for (int i = 0; i < 10; i++) {
             matrix[i][i] = i;
        }
        for (int i = 9, j = 0; j < 10; i--, j++) {
            matrix[i][j] = j;
        }
    }
    else if (dim == 3) {
        matrix[1][2][3] = 100;
        ((matrix[0][1][2] = 314) = 0) = 217;
    }
    else if (dim == 4) {
        matrix[1][2][3][4] = 100;
    }

    std::cout << "size = " << matrix.size() << std::endl;
    matrix.print();

    return 0;
}