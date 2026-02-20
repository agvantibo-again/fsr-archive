#include "queue-array-naive.h"

void print_impl(char *restrict fmt) { printf(fmt, QUEUE_IMPL); }

struct Queue mkQueue() {
  int *new_array = calloc(QUEUE_INITIAL_CAP, sizeof(int));
  return (struct Queue){.rear = QUEUE_EMPTY,
                        .cap = QUEUE_INITIAL_CAP,
                        .len = 0,
                        .store = new_array};
}
// one thing to note: i *REALLY* dislike how this doesn't provide to us
// the invariant that QUEUE->front is something valid, unlike the list version
// but it's C anyway so theoretically anything could access and invalidate
// .store and invariants don't matter and i don't matter and nothing even
// matters

// so by checking for NULL every "method" call I'm doing a Good Thing™

enum RetCode Queue_push(struct Queue *q, int const a) {
  if (!q || !q->store) {
    return MEM_ERROR;
  }
  ++q->rear;
  int *old_store;
  if (q->rear >= q->cap) { // overflow
    old_store = q->store;
    q->cap *= 2;
    q->store = realloc(old_store, (unsigned long)q->cap * sizeof(int));
    if (!q->store) {
      q->store = old_store;
      return MEM_ERROR;
    }
  }
  q->store[q->rear] = a;
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
  *a = q->store[0];
  return OK;
}

enum RetCode Queue_pop(struct Queue *q, int *a) {
  enum RetCode ret = Queue_front(q, a);
  if (ret) { // any errors
    return ret;
  }
  for (int i = 1; i <= q->rear; i++) {
    q->store[i - 1] = q->store[i];
  }
  --q->rear;
  --q->len;
  return OK;
}

enum RetCode Queue_clear(struct Queue *q) {
  free(q->store);
  q->store = NULL;
  return OK;
}
