#include <stdio.h>
#include <stdlib.h>

#ifndef AGV_QUEUE
#define AGV_QUEUE
enum RetCode {
  OK = 0,
  EMPTY = 1,
  MEM_ERROR = 2
};

struct ListItem {
  int v;
  struct ListItem *p, *n;
};

struct Queue {
  size_t size;
  struct ListItem *top, *bot;
};

struct Queue mkQueue()
{
  return (struct Queue){.size = 0, .top = NULL, .bot = NULL};
}

enum RetCode Queue_push(struct Queue* q, int const a) {
  struct ListItem* new = malloc(sizeof(struct ListItem));
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

enum RetCode Queue_front(struct Queue* const q, int* a) {
  if (q->top == NULL) {
    return EMPTY;
  }
  *a = q->top->v;
  return OK;
}

enum RetCode Queue_pop(struct Queue* q, int* a) {
  if (q->top == NULL) {
    return EMPTY;
  }
  *a = q->top->v;
  struct ListItem* old_top = q->top;
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

enum RetCode Queue_clear(struct Queue* q) {
  struct ListItem* i = q->top;
  while (i != NULL) {
    struct ListItem* tmp = i->p;
    free(i);
    i = tmp;
  }
  *q = mkQueue();
  return OK;
}

#endif // AGV_QUEUE

enum RetCode Queue_insert_mid(struct Queue* q, int const a) {
  if (q->size == 0) {
    return Queue_push(q, a);
  }
  size_t const index = q->size / 2;
  struct ListItem* cur = q->bot;
  for (size_t i = 0; i < index; ++i) {
    cur = cur->n;
  }
  struct ListItem* new_item = malloc(sizeof(struct ListItem));
  if (!new_item) {
    return MEM_ERROR;
  }
  new_item->v = a;
  new_item->n = cur;
  new_item->p = cur->p;
  if (cur->p) {cur->p->n = new_item;}
  if (index == 0) { q->bot = new_item;}
  cur->p = new_item;
  ++q->size;
  return OK;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  struct Queue q = mkQueue();
  enum RetCode ret;
  int buf;
  int n_cmds;
  int op;
  scanf("%d", &n_cmds);
  for (int i = 0; i < n_cmds; ++i) {
    do {
      op = getchar();
    } while (op != '+' && op != '*'  && op != '-');
    switch (op) {
      case '+':
        scanf("%d", &buf);
        ret = Queue_push(&q, buf);
        break;
      case '*':
        scanf("%d", &buf);
        ret = Queue_insert_mid(&q, buf);
        break;
      case '-':
        ret = Queue_pop(&q, &buf);
        printf("%d\n", buf);
        break;
    }
    if (ret == MEM_ERROR) {
      Queue_clear(&q);
      return 2;
    }
  }
  Queue_clear(&q);
  return 0;
}
