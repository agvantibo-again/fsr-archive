#include <stdio.h>
#include <time.h>
#include "agv/queue-array-naive.h"

struct Queue* genQueue(int const n) {
  struct Queue* q = malloc(sizeof(struct Queue));
  *q = mkQueue();
  int ret = OK;
    for (int i = 0; i < n; ++i) {
      ret += Queue_push(q, i);
  }
  if (ret) { // any errors returned?
    q = NULL;
    fprintf(
      stderr,
      "\nErrors were detected when calling genQueue with value %d\n",
      n
    );
  }
  return q;
}

void measure_insert(int const n) { // leaks memory!
  struct Queue* q [[maybe_unused]] = genQueue(n);
}


void measure_insert_destroy(int const n) {
  struct Queue* q = genQueue(n);
  Queue_clear(q);
  free(q);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  #define TAB_L 8
  #define MAX_NAME 24
  // There is no good way i know of to do this painlessly at compile-time
  // X-macros (defining the benchmark suite as calls to macro X and then redefining 
  // X() several times throughout the source file) could help if i've had more tests

  #define MEASURE_T(f) t[i++] = clock(); f; t[i++] = clock();
  #define ADD_TABS(name) for (int _i = sizeof name; _i <= MAX_NAME; _i += TAB_L) \
    {putchar('\t');}
  #define BENCH_N(name, n, action) printf("%s %s:", name, #n); \
    MEASURE_T(action(n)) \
    dt = t[i - 1] - t[i - 2]; \
    ADD_TABS(name) \
    printf("%ldc (%Lfms)\n", dt, (long double) dt / CLOCKS_PER_SEC * 1000);

  long t[16];
  int i = 0;
  long dt;
  printf("CLOCKS_PER_SEC defined as %ld\n\n", CLOCKS_PER_SEC);
  
  BENCH_N("Insertion", 32768, measure_insert);
  BENCH_N("Insertion", 131072, measure_insert);
  BENCH_N("Insertion", 524288, measure_insert);

  BENCH_N("Insertion & destruction", 32768, measure_insert_destroy);
  BENCH_N("Insertion & destruction", 131072, measure_insert_destroy);
  BENCH_N("Insertion & destruction", 524288, measure_insert_destroy);

  return 0;
}
