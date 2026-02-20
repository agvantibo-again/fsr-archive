
#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>
#define IS_ALPHA(ch) ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z')
#define COMMAND_MAX_LENGTH 32

enum Operation { PUSH, POP, FRONT, SIZE, CLEAR, EXIT, FAILURE = 128 };

enum RetCode { OK = 0, EMPTY = 1, MEM_ERROR = 2 };

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
  q->size += 1;
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
  q->size -= 1;
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

enum Operation get_operation() {
  int b;
  do {
    b = getchar();
  } while (!IS_ALPHA(b));

  char command[COMMAND_MAX_LENGTH + 1];
  command[COMMAND_MAX_LENGTH] = '\0';
  int i = 0;
  do {
    command[i] = (char)b;
    b = getchar();
    ++i;
  } while (IS_ALPHA(b) && i < COMMAND_MAX_LENGTH);

  switch (command[0]) {
  case 'p':
    switch (command[1]) {
    case 'u':
      return PUSH;
    case 'o':
      return POP;
    default:
      return EXIT;
    }
  case 'f':
    return FRONT;
  case 's':
    return SIZE;
  case 'c':
    return CLEAR;
  case 'e':
    return EXIT;
  default:
    return FAILURE;
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  struct Queue q = mkQueue();
  enum Operation op;
  enum RetCode ret;
  int buf = -1;
  do {
    op = get_operation();
    switch (op) {
    case PUSH:
      scanf("%d", &buf);
      ret = Queue_push(&q, buf);
      break;
    case POP:
      ret = Queue_pop(&q, &buf);
      break;
    case FRONT:
      ret = Queue_front(&q, &buf);
      break;
    case SIZE:
      buf = (int)q.size;
      ret = OK;
      break;
    case CLEAR:
      ret = Queue_clear(&q);
      break;
    case EXIT:
      ret = Queue_clear(&q);
      break;
    default:
      return EMPTY;
    }
    if (ret == OK) {
      if (op == FRONT || op == SIZE || op == POP) {
        printf("%d\n", buf);
      } else if (op == EXIT) {
        printf("bye\n");
      } else {
        printf("ok\n");
      }
    } else if (ret == MEM_ERROR) {
      return MEM_ERROR;
    } else {
      printf("error\n");
    }
  } while (op != EXIT);

  return OK;
}
