#include "queue.h"

#ifndef AGV_QUEUE_LIST
#define AGV_QUEUE_LIST

#define QUEUE_IMPL "list"
struct ListItem {
  int v;
  struct ListItem *p, *n;
};

struct Queue {
  size_t len;
  struct ListItem *top, *bot;
};
struct Queue mkQueue();

#endif // AGV_QUEUE_LIST