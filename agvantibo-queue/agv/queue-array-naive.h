#include "queue.h"

#ifndef AGV_QUEUE_ARR_BAD
#define AGV_QUEUE_ARR_BAD

#define QUEUE_EMPTY -1
#define QUEUE_INITIAL_CAP 256
#define QUEUE_IMPL "array-naive"

struct Queue {
  int rear;
  int cap;
  int len;
  int* store;
};

#endif // AGV_QUEUE_ARR_BAD