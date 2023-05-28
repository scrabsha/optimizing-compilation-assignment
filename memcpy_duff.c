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

void *memcpy__(char *dest, const char *src, size_t n) {
  char *d = dest;

  switch (n % 8) {
  case 0:
    while (n--) {
      *d++ = *(char *)src++;
    case 7:
      *d++ = *(char *)src++;
    case 6:
      *d++ = *(char *)src++;
    case 5:
      *d++ = *(char *)src++;
    case 4:
      *d++ = *(char *)src++;
    case 3:
      *d++ = *(char *)src++;
    case 2:
      *d++ = *(char *)src++;
    case 1:
      *d++ = *(char *)src++;
    }
  }

  return dest;
}

// TEST: #include <stddef.h>
// TEST: #include <string.h>
// TEST: #include <stdlib.h>
// TEST: void *memcpy__(void *dest, const void *src, size_t n);
// TEST: #define BEFORE_LOOP() char dest[100]; \
// TEST:                      char src[100]; \
// TEST:                      memset(dest, 0, 100); \
// TEST:                      memset(src, 0, 100)
// TEST: #define LOOP() memcpy__(dest, src, 100)
// TEST: #define AFTER_LOOP()
