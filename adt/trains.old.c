#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef AGV_QUEUE
#define AGV_QUEUE
enum RetCode { OK = 0, NOPE = 1, MEM_ERROR = 2 };
// #define true false
struct ListItem {
  int v;
  struct ListItem *p, *n;
};

struct Queue {
  size_t size;
  struct ListItem *top, *bot;
};

struct Queue mkQueue() {
  return (struct Queue){.size = 0, .top = NULL, .bot = NULL};
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
  ++q->size;
  return OK;
}

enum RetCode Queue_front(struct Queue *const q, int *a) {
  if (q->top == NULL) {
    return NOPE;
  }
  *a = q->top->v;
  return OK;
}

enum RetCode Queue_pop(struct Queue *q, int *a) {
  if (q->top == NULL) {
    return NOPE;
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
  --q->size;
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

#endif // AGV_QUEUE

#ifndef AGV_STACK
#define AGV_STACK

#define STACK_INITIAL_CAP 256
// enum RetCode
// {
//   OK = 0,
//   NOPE = 1,
//   MEM_ERROR = 2,
// };

struct Stack {
  int cap;
  int b;
  int *s;
};

enum RetCode Stack_init(struct Stack *st) {
  st->cap = STACK_INITIAL_CAP;
  st->b = -1;
  st->s = calloc(STACK_INITIAL_CAP, sizeof(int));
  return (st->s != NULL) ? OK : MEM_ERROR;
}

enum RetCode Stack_push(struct Stack *st, int const a) {
  ++st->b;
  int *old_s = st->s;
  if (st->b >= st->cap) {
    st->s = realloc(st->s, (size_t)(2 * st->cap) * sizeof(int));
    if (st->s == NULL) {
      st->s = old_s;
      return MEM_ERROR;
    }
  }
  st->s[st->b] = a;
  return OK;
}

enum RetCode Stack_pop(struct Stack *st, int *a) {
  if (st->b == -1) {
    return NOPE;
  }
  *a = st->s[st->b];
  --st->b;
  return OK;
}

enum RetCode Stack_back(struct Stack *const st, int *a) {
  if (st->b == -1) {
    return NOPE;
  }
  *a = st->s[st->b];
  return OK;
}

enum RetCode Stack_size(struct Stack *const st, int *a) {
  *a = st->b + 1;
  return OK;
}

enum RetCode Stack_clear(struct Stack *st) {
  st->b = -1;
  return OK;
}

enum RetCode Stack_destroy(struct Stack *st) {
  Stack_clear(st);
  free(st->s);
  st->s = NULL;
  return OK;
}

#endif // AGV_STACK

int min(size_t len, int a[len]) {
  int min = INT_MAX;
  for (size_t i = 0; i < len; ++i) {
    min = (min > a[i]) ? a[i] : min;
  }
  return min;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
#define MEM_PANIC_IF(arg)                                                      \
  do {                                                                         \
    if (arg == MEM_ERROR) {                                                    \
      Stack_destroy(&st);                                                      \
      Queue_clear(&q);                                                         \
      return 2;                                                                \
    }                                                                          \
  } while (0)
  // AKA why we need goto
  int n;
  scanf("%d", &n);
  if (n <= 0) {
    return 1;
  }
  int trains[n];
  for (int i = 0; i < n; ++i) {
    scanf("%d", trains + i);
  }
  int tr1 = 0;
  int tgt = min((size_t)n, trains);
  int buf;
  enum RetCode ret;
  struct Queue q = mkQueue();
  struct Stack st;
  ret = Stack_init(&st);
  MEM_PANIC_IF(ret);
  //   bool solveable = true;
  while (tr1 < n) {
    ret = Stack_back(&st, &buf);
    MEM_PANIC_IF(ret);
    if (ret == OK && buf == tgt) {
      ret = Queue_push(&q, 2);
      MEM_PANIC_IF(ret);
      Stack_pop(&st, &buf);
    } else if (trains[tr1] == tgt) {
      ret = Queue_push(&q, 1);
      MEM_PANIC_IF(ret);
      ret = Queue_push(&q, 2);
      MEM_PANIC_IF(ret);
      trains[tr1++] = INT_MAX;
      tgt = min((size_t)n, trains);
    } else {
      ret = Queue_push(&q, 1);
      MEM_PANIC_IF(ret);
      ret = Stack_push(&st, trains[tr1]);
      MEM_PANIC_IF(ret);
      trains[tr1++] = INT_MAX;
      tgt = min((size_t)n, trains);
      // ret = Stack_back(&ic, &buf);
      // MEM_PANIC_ON(ret);
      // if (ret == OK && buf == tgt) {
      //   ret = Queue_push(&ostream, 2);
      //   MEM_PANIC_ON(ret);
      //   Stack_pop(&ic, &buf);
      // } else if (cars[tr1] == tgt) {
      //   ret = Queue_push(&ostream, 1);
      //   MEM_PANIC_ON(ret);
      //   ret = Queue_push(&ostream, 2);
      //   MEM_PANIC_ON(ret);
      //   cars[tr1++] = INT_MAX;t);
      //   tgt = min((size_t) n, cars);
      // } else {
      //   ret = Queue_push(&ostream, 1);
      //   MEM_PANIC_ON(ret);
      //   ret = Stack_push(&ic, cars[tr1]);
      //   MEM_PANIC_ON(ret);
      //   cars[tr1++] = INT_MAX;
      //   tgt = min((size_t) n, cars);
      //   }
    }
  }
  while (!Queue_front(&q, &buf)) {
    printf("%d 1\n", buf);
    // could write fancy schmancy node compression code here
    // to output multiple operations at once
    // but it's 1am and i have other tasks at hand
    Queue_pop(&q, &buf);
  }
  Stack_destroy(&st);
  Queue_clear(&q);
  return 0;
}
