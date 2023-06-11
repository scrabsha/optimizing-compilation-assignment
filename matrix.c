// Source:
// https://www.geeksforgeeks.org/c-program-multiply-two-matrices/
//
// RUN(gcc-0): gcc -O0
// RUN(gcc-1): gcc -O1
// RUN(gcc-2): gcc -O2
// RUN(gcc-3): gcc -O3
//
// RUN(clang-0): clang -O0
// RUN(clang-1): clang -O1
// RUN(clang-2): clang -O2
// RUN(clang-3): clang -O3
//
// RUN(icc-0): icc -O0
// RUN(icc-1): icc -O1
// RUN(icc-2): icc -O2
// RUN(icc-3): icc -O3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VALUE 50

// Multiplies two matrices mat1[][] and mat2[][]
// and prints result.
// (m1) x (m2) and (n1) x (n2) are dimensions
// of given matrices.
void multiply(int m1, int m2, int mat1[][m2], int n1, int n2, int mat2[][n2]) {
  int x, i, j;
  int res[m1][n2];
  for (i = 0; i < m1; i++) {
    for (j = 0; j < n2; j++) {
      res[i][j] = 0;
      for (x = 0; x < m2; x++) {
        *(*(res + i) + j) += *(*(mat1 + i) + x) * *(*(mat2 + x) + j);
      }
    }
  }
}

int randint() { return rand() % MAX_VALUE; }

int matrix() {
  srand(time(NULL));
  int mat1[5][5];
  int mat2[5][5];

  for (size_t i = 0; i < 5; i++) {
    for (size_t j = 0; j < 5; j++) {
      mat1[i][j] = randint();
      mat2[i][j] = randint();
    }
  }

  int m1 = 5, m2 = 5, n1 = 5, n2 = 5;

  multiply(m1, m2, mat1, n1, n2, mat2);
  return 0;
}

// TEST: #include <stdbool.h>
// TEST: extern int matrix();
// TEST: #define BEFORE_LOOP()
// TEST: #define LOOP() matrix()
// TEST: #define AFTER_LOOP()
