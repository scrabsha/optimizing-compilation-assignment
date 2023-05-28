#include "test.h"
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>

int main() {
  // store current time
  struct timeval start, end;
  gettimeofday(&start, NULL);

  BEFORE_LOOP();
  for (int i = 0; i < 10000; i++) {
    LOOP();
  }
  AFTER_LOOP();

  // store current time
  gettimeofday(&end, NULL);

  // calculate and print the elapsed time in microseconds
  double elapsed =
      (end.tv_sec - start.tv_sec) * 1000000.0 + end.tv_usec - start.tv_usec;

#ifdef DIVIDER
  elapsed /= DIVIDER;
#endif

  printf("%f\n", elapsed);

  return 0;
}