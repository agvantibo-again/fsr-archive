#include "queue-array.h"

void print_impl(char *restrict fmt) { printf(fmt, QUEUE_IMPL); }

struct Queue mkQueue() {
  int *new_array = calloc(QUEUE_INITIAL_CAP, sizeof(int));
  return (struct Queue){.front = 0,
                        .rear = 0,
                        .len = 0,
                        .cap = QUEUE_INITIAL_CAP,
                        .store = new_array};
} // still hatin'

enum RetCode Queue_push(struct Queue *q, int const a) {
  if (!q || !q->store) {
    return MEM_ERROR;
  }
  int *old_store;
  int new_front;
  if (q->len >= q->cap) { // overflow
    old_store = q->store;
    new_front = q->front + q->cap;
    q->cap *= 2; // += q->cap but faster
    q->store = realloc(old_store, (unsigned long)q->cap * sizeof(int));
    if (!q->store) {
      q->store = old_store;
      return MEM_ERROR;
    }
    memcpy(&q->store[new_front], &q->store[q->front],
           sizeof(int) * (size_t)(q->len - q->front));
    q->front = new_front;
  }
  q->store[q->rear] = a;
  q->rear = (q->rear + 1) % q->cap;
  ++q->len;

  return OK;
}

enum RetCode Queue_front(struct Queue *const q, int *a) {
  if (!q || !q->store) {
    return MEM_ERROR;
  }
  if (!q->len) {
    return EMPTY;
  }
  *a = q->store[q->front];
  return OK;
}

enum RetCode Queue_pop(struct Queue *q, int *a) {
  enum RetCode ret = Queue_front(q, a);
  if (ret) { // any errors
    return ret;
  }
  *a = q->store[q->front];
  q->front = (q->front + 1) % q->cap;
  --q->len;
  return OK;
}

enum RetCode Queue_clear(struct Queue *q) {
  free(q->store);
  q->store = NULL;
  return OK;
}
