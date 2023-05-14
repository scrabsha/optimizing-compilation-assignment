// Source:
// https://developers.redhat.com/blog/2019/03/13/intro-jump-threading-optimizations#
//
// RUN(gcc-o1-disabled): gcc -O1 -fno-thread-jumps
// RUN(gcc-o1-enabled): gcc -O1 -fthread-jumps
// RUN(gcc-o2-disabled): gcc -O2 -fno-thread-jumps
// RUN(gcc-o2-enabled): gcc -O2 -fthread-jumps
//
// RUN(clang-o1-disabled): clang -O1 -fthread-jumps
// RUN(clang-o1-enabled): clang -O0 -fthread-jumps

#include <stddef.h>

extern void foo(void);
extern void bar(void);

void foo_(int a, int b, int c) {
  if (a && b)
    foo();
  if (b || c)
    bar();
}