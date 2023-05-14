// RUN(gcc-0): gcc -O0
// RUN(gcc-1): gcc -O1
// RUN(gcc-2): gcc -O2
// RUN(gcc-3): gcc -O3
//
// RUN(clang-0): clang -O0
// RUN(clang-1): clang -O1
// RUN(clang-2): clang -O2
// RUN(clang-3): clang -O3

#include <stddef.h>

void *memcpy_(void *dest, const void *src, size_t n) {
  char *d = dest;
  const char *s = src;
  while (n--)
    *d++ = *s++;
  return dest;
}

// TEST: #include <stddef.h>
// TEST: #include <string.h>
// TEST: #include <stdlib.h>
// TEST: #include <assert.h>
// TEST: void *memcpy_(void *dest, const void *src, size_t n);
// TEST: #define BEFORE_LOOP() void *dest = malloc(1000); \
// TEST:                      void *src = malloc(1000); \
// TEST:                      memset(dest, 0, 1000); \
// TEST:                      memset(src, 0, 1000)
// TEST: #define LOOP() memcpy_(dest, src, 1000)
// TEST: #define AFTER_LOOP() free(dest); \
// TEST:                     free(src)
