
#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>

enum Operations {
  HALT = 0,
  PUSH = 1,
  POP = 2,
  FRONT = 3,
  IS_EMPTY = 4,
  CLEAR = 5
};

enum RetCodes { OK = 0, EMPTY = 1, MEM_ERROR = 2 };

struct ListItem {
  int v;
  struct ListItem *p, *n;
};

struct Queue {
  struct ListItem *top, *bot;
};

int Queue_init(struct Queue *q) {
  q->top = q->bot = NULL;
  return OK;
}

int Queue_push(struct Queue *q, int const a) {
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
  return OK;
}

int Queue_top(struct Queue *const q, int *a) {
  if (q->top == NULL) {
    return EMPTY;
  }
  *a = q->top->v;
  return OK;
}

int Queue_pop(struct Queue *q, int *a) {
  if (q->top == NULL) {
    return EMPTY;
  }
  *a = q->top->v;
  if (q->top->p == NULL) {
    free(q->top);
    q->top = q->bot = NULL;
  } else {
    q->top = q->top->p;
    free(q->top->n);
    q->top->n = NULL;
  }
  return OK;
}

int Queue_clear(struct Queue *q) {
  struct ListItem *i = q->top;
  while (i != NULL) {
    struct ListItem *tmp = i->p;
    free(i);
    i = tmp;
  }
  q->top = q->bot = NULL;
  return OK;
}

int is_Queue_empty(struct Queue *const q) { return (q->top == NULL); }

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  enum Operations op;
  int buf, ret;
  struct Queue q;
  Queue_init(&q);
  do {
    scanf("%d", &op);
    switch (op) {
    case PUSH:
      scanf("%d", &buf);
      ret = Queue_push(&q, buf);
      break;
    case POP:
      ret = Queue_pop(&q, &buf);
      break;
    case FRONT:
      ret = Queue_top(&q, &buf);
      break;
    case IS_EMPTY:
      ret = is_Queue_empty(&q);
      break;
    case CLEAR:
      ret = Queue_clear(&q);
      break;
    default:
      ret = 0;
      break;
    }
    if (ret == 2) {
      return 1;
    } else if (op == IS_EMPTY) {
      printf("%d\n", ret);
    } else if (ret == 1) {
      printf("Queue is empty\n");
    } else if (op == FRONT) {
      printf("%d\n", buf);
    }
  } while (op != 0);

  return 0;
}
