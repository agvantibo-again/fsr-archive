// #include <string.h>
#include "queue.h"

#ifndef AGV_QUEUE_ARR
#define AGV_QUEUE_ARR

#define QUEUE_EMPTY -1
#define QUEUE_INITIAL_CAP 3
#define QUEUE_IMPL "array"

struct Queue {
  int front, rear;
  int cap;
  int len;
  int* store;
};

#endif // AGV_QUEUE_ARR