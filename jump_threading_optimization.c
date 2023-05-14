// Source:
// https://developers.redhat.com/blog/2019/03/13/intro-jump-threading-optimizations#
//
// RUN(gcc-o1-disabled): gcc -O1 -fno-thread-jumps
// RUN(gcc-o1-enabled): gcc -O1 -fthread-jumps
// RUN(gcc-o2-disabled): gcc -O2 -fno-thread-jumps
// RUN(gcc-o2-enabled): gcc -O2 -fthread-jumps

void foo(void) { asm(""); }

void bar(void) { asm(""); }

void foo_(int a, int b, int c) {
  if (a && b)
    foo();
  if (b || c)
    bar();
}

// TEST: extern void foo_(int a, int b, int c);
// TEST: #define BEFORE_LOOP()
// TEST: #define LOOP() foo_(0, 0, 0) ; \
// TEST:                foo_(0, 0, 1) ; \
// TEST:                foo_(0, 1, 0) ; \
// TEST:                foo_(0, 1, 1) ; \
// TEST:                foo_(1, 0, 0) ; \
// TEST:                foo_(1, 0, 1) ; \
// TEST:                foo_(1, 1, 0) ; \
// TEST:                foo_(1, 1, 1)
// TEST: #define AFTER_LOOP()
// TEST: #define DIVIDER 8
