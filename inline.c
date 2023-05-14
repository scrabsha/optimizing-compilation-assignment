// RUN(gcc-0): gcc -O0
// RUN(gcc-1): gcc -O1
// RUN(gcc-2): gcc -O2
// RUN(gcc-3): gcc -O3

#include <stdbool.h>

static inline int f(bool a) { return !a; }

bool g(bool a) { return !f(a); }

// TEST: #include <stdbool.h>
// TEST: extern bool g(bool a);
// TEST: #define BEFORE_LOOP()
// TEST: #define LOOP() g(false)
// TEST: #define AFTER_LOOP()
