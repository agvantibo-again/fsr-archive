#include "queue-list.h"

void print_impl(char *restrict fmt) { printf(fmt, QUEUE_IMPL); }

struct Queue mkQueue() {
  return (struct Queue){.len = 0, .top = NULL, .bot = NULL};
}

enum RetCode Queue_push(struct Queue *q, int const a) {
  struct ListItem *new = malloc(sizeof(struct ListItem));
  if (new == NULL) {
    return MEM_ERROR;
  }
  new->v = a;
  if (q->bot == NULL) {
    q->top = q->bot = new;
    q->bot->p = q->bot->n = NULL;
  } else {
    new->n = q->bot;
    q->bot->p = new;
    new->p = NULL;
    q->bot = new;
  }
  ++q->len;
  return OK;
}

enum RetCode Queue_front(struct Queue *const q, int *a) {
  if (q->top == NULL) {
    return EMPTY;
  }
  *a = q->top->v;
  return OK;
}

enum RetCode Queue_pop(struct Queue *q, int *a) {
  if (q->top == NULL) {
    return EMPTY;
  }
  *a = q->top->v;
  struct ListItem *old_top = q->top;
  if (old_top->p) {
    q->top = old_top->p;
    q->top->n = NULL;
  } else {
    q->top = q->bot = NULL;
  }
  free(old_top);
  --q->len;
  return OK;
}

enum RetCode Queue_clear(struct Queue *q) {
  struct ListItem *i = q->top;
  while (i != NULL) {
    struct ListItem *tmp = i->p;
    free(i);
    i = tmp;
  }
  *q = mkQueue();
  return OK;
}