#include "test.h"
#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define ITERATIONS 1000000

typedef struct {
  clock_t start;
  clock_t end;
} measurement;

measurement measurements[ITERATIONS];

// Returns the mean value of the measurements in microseconds
double mean() {
  assert(CLOCKS_PER_SEC == 1000000);

  double sum = 0;
  for (int i = 0; i < ITERATIONS; i++) {
    sum += (double)(measurements[i].end - measurements[i].start);
  }
  return sum / ITERATIONS;
}

// Returns the standard deviation of the measurements in microseconds
double std_dev(double mean) {
  double sum = 0;
  for (int i = 0; i < ITERATIONS; i++) {
    double diff = (double)(measurements[i].end - measurements[i].start) - mean;
    sum += diff * diff;
  }
  return sqrt(sum / ITERATIONS);
}

int main() {
  BEFORE_LOOP();

  for (int i = 0; i < ITERATIONS; i++) {
    clock_t start = clock();
    LOOP();
    clock_t end = clock();

    measurements[i].start = start;
    measurements[i].end = end;
  }

  AFTER_LOOP();

  double mean_time = mean();
  double std_dev_time = std_dev(mean_time);

#ifdef DIVIDER
  int divider = DIVIDER;
  mean_time /= (double)divider;
  std_dev_time /= (double)divider;
#endif

  printf("%f,%f\n", mean_time, std_dev_time);

  return 0;
}