// I have not managed to make this test produce anything useful. I think the
// compiler is being a little bit too smart. For this.
//
// Source:
// https://developers.redhat.com/blog/2019/03/13/intro-jump-threading-optimizations#
//
// RUN(gcc-0-0): gcc -fno-thread-jumps -O0
// RUN(gcc-0-1): gcc -fthread-jumps -O0
//
// RUN(gcc-1-0): gcc -fno-thread-jumps -O1
// RUN(gcc-1-1): gcc -fthread-jumps -O1
//
// RUN(gcc-2-0): gcc -fno-thread-jumps -O2
// RUN(gcc-2-1): gcc -fthread-jumps -O2
//
// RUN(gcc-3-0): gcc -fno-thread-jumps -O3
// RUN(gcc-3-1): gcc -fthread-jumps -O3
//
// RUN(gcc-s-0): gcc -fno-thread-jumps -Os
// RUN(gcc-s-1): gcc -fthread-jumps -Os

extern int stuff(void);

int main(int a, char **b) {
  if (a > 5)
    goto j;
  stuff();
  stuff();
j:
  goto somewhere;

  stuff();
  stuff();

somewhere:
  return 0;
}