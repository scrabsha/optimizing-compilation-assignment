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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VALUE 50

// (m1) x (m2) and (n1) x (n2) are dimensions
// of given matrices.
void multiply(int n, int p, int mat1[n * p], int mat2[p * n], int res[n * n]) {
  int x, i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      res[i * n + j] = 0;
      for (x = 0; x < p; x++) {
        res[i * n + j] += mat1[i * p + x] * mat2[x * n + j];
      }
    }
  }
}

int randint() { return rand() % MAX_VALUE; }

int matrix() {
  srand(time(NULL));
  int mat1[] = {randint(), randint(), randint(), randint()};
  int mat2[] = {randint(), randint(), randint(), randint()};
  int res[] = {0};
  int m1 = 2, m2 = 2, n1 = 2, n2 = 2;

  multiply(m1, m2, mat1, mat2, res);
  return 0;
}

// TEST: #include <stdbool.h>
// TEST: extern int matrix();
// TEST: #define BEFORE_LOOP()
// TEST: #define LOOP() matrix()
// TEST: #define AFTER_LOOP()
