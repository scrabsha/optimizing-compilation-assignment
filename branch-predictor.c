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

#include <stddef.h>

// Example of test function:
#define PERCENTAGE_TRUE 50;

int test(void) {
  asm("");
  static int i = 0;
  return i++ % 100 < PERCENTAGE_TRUE;
}

extern int test(void);

int perform_long_loop(char *out, size_t n) {
  for (int i = 0; i < n; i++) {
    if (test()) {
      out[i] = 0;
    } else {
      out[i] = 1;
    }
  }

  return 0;
}

// TEST: #include <stddef.h>
// TEST: #define BEFORE_LOOP() char out[10000];
// TEST: extern int perform_long_loop(char *out, size_t n);
// TEST: #define LOOP() perform_long_loop(out, 10000)
// TEST: #define AFTER_LOOP()
