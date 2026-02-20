
#include <stdio.h>
#include <stdlib.h>

#include "agv/queue-array.h"
// #include <stdbool.h>
#define IS_ALPHA(ch) ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z')
#define COMMAND_MAX_LENGTH 32

enum Operation { PUSH, POP, FRONT, SIZE, CLEAR, EXIT, FAILURE = 128 };

enum Operation get_operation() {
  int b;
  printf(">> ");
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
  print_impl("Today's implementation of queue is %s\n\n");
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
      buf = (int)q.len;
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
