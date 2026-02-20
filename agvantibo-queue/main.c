#include "agv/queue-list.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

struct EvilQueue { //     >:3
  struct Queue *queue;
  long double time;
};

struct EvilQueue genQueue(int const n) {
  struct Queue *q = malloc(sizeof(struct Queue));
  time_t pre, post, sum = 0;
  *q = mkQueue();
  int ret = OK;
  for (int i = 0; i < n; ++i) {
    pre = clock();
    ret += Queue_push(q, i);
    post = clock();
    sum += post - pre;
  }

  if (ret) { // any errors returned?
    q = NULL;
    fprintf(stderr,
            "\nErrors were detected when calling genQueue with value %d\n", n);
  }
  return (struct EvilQueue){.queue = q, .time = (long double)sum / n};
}

long double measure_insert(int const n) { // no longer leaks memory!
  struct EvilQueue eq = genQueue(n);
  struct Queue *q [[maybe_unused]] = eq.queue;
  Queue_clear(q);
  return eq.time;
}

long double measure_extract(int const n) {
  struct EvilQueue eq = genQueue(n);
  struct Queue *q = eq.queue;
  int val [[maybe_unused]];
  time_t pre, post, sum = 0;
  for (int i = 0; i < n; ++i) {
    pre = clock();
    Queue_pop(q, &val);
    post = clock();
    sum += post - pre;
    if (val != i) { // throw a hissy fit
      printf("Queue is returning incorrect elements: expected %d, got %d\n", i,
             val);
    }
  }
  Queue_clear(q);
  return (long double)sum / n;
}

long double measure_insert_destroy(int const n) {
  struct EvilQueue eq = genQueue(n);
  struct Queue *q = eq.queue;
  time_t pre, post;
  pre = clock();
  Queue_clear(q);
  post = clock();
  free(q);
  return (long double)post - pre;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
#define TAB_L 8
#define MAX_NAME 24
#define SAMPLES 8
#define EVIL_ASS_FORMAT_S "%Lfclk (%Lfms)\n"
  // There is no good way i know of to do this painlessly at compile-time
  // X-macros (defining the benchmark suite as calls to macro X and then
  // redefining X() several times throughout the source file) could help if i've
  // had more tests

#define ADD_TABS(name)                                                         \
  for (int _i = sizeof name; _i <= MAX_NAME; _i += TAB_L) {                    \
    putchar('\t');                                                             \
  }
#define _BENCH_N(name, n, action)                                              \
  printf("%s (%s):", name, #n);                                                \
  ct = action(n);                                                              \
  ADD_TABS(name)                                                               \
  printf(EVIL_ASS_FORMAT_S, ct, (long double)ct / CLOCKS_PER_SEC * 1000);

#define BENCH_N(name, n, action, times)                                        \
  st = 0;                                                                      \
  for (int _j = 0; _j < times; ++_j) {                                         \
    _BENCH_N(name, n, action);                                                 \
    st += ct;                                                                  \
  }                                                                            \
  printf("Average results for %s (%s): ", name, #n);                           \
  printf(EVIL_ASS_FORMAT_S, (long double)st / times,                           \
         (long double)st / times / CLOCKS_PER_SEC * 1000);

  long double st;
  long double ct;
  printf("CLOCKS_PER_SEC defined as %ld\n", CLOCKS_PER_SEC);
  print_impl("Today's implementation of queue is %s\n\n");

  BENCH_N("Insertion", 32768, measure_insert, SAMPLES);
  BENCH_N("Insertion", 131072, measure_insert, SAMPLES);
  BENCH_N("Insertion", 524288, measure_insert, SAMPLES);

  BENCH_N("Extraction", 32768, measure_extract, SAMPLES);
  BENCH_N("Extraction", 131072, measure_extract, SAMPLES);
  if (strcmp("array-naive", QUEUE_IMPL) != 0) {
    BENCH_N("Extraction", 524288, measure_extract, SAMPLES);
  } else {
    printf("Skipped due to %s implementation\n", QUEUE_IMPL);
  } // trust me on this one

  BENCH_N("Destruction", 131072, measure_insert_destroy, SAMPLES);
  BENCH_N("Destruction", 32768, measure_insert_destroy, SAMPLES);
  BENCH_N("Destruction", 524288, measure_insert_destroy, SAMPLES);

  return 0;
}
