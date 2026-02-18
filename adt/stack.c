
#include <stdio.h>
#include <stdlib.h> // calloc(), realloc(), free()
#include <string.h> // strcmp()

#define STACK_INITIAL_CAP 256
#define COMMAND_MAX_LENGTH 32
#define IS_ALPHA(ch) ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z')

// char const *operations[COMMAND_MAX_CODE] = {
//   "exit",
//   "push",
//   "pop",
//   "back",
//   "size",
//   "clear",
// };

enum Operation {
  EXIT,
  PUSH,
  POP,
  BACK,
  SIZE,
  CLEAR,
  FAILURE = 128,
};

enum RetCode {
  OK = 0,
  EMPTY = 1,
  MEM_ERROR = 2,
};

struct Stack {
  int cap;
  int b;
  int * s;
};

// static inline int max(int const a, int const b) {
//   return a > b ? a : b;
// }

int Stack_init(struct Stack* st) {
  st->cap = STACK_INITIAL_CAP;
  st->b = -1;
  st->s = calloc(STACK_INITIAL_CAP, sizeof(int));
  return (st->s != NULL) ? OK : MEM_ERROR;
}

int Stack_push(struct Stack* st, int const a) {
  ++st->b;
  int * old_s = st->s;
  if (st->b >= st->cap) {
    st->s = realloc(st->s, (size_t)(2*st->cap) * sizeof(int));
    if (st->s == NULL) {
      st->s = old_s;
      return MEM_ERROR;
    }
  }
  st->s[st->b] = a;
  return OK;
}

int Stack_pop(struct Stack* st, int* a) {
  if (st->b == -1) {
    return EMPTY;
  }
  *a = st->s[st->b];
  --st->b;
  return OK;
}

int Stack_back(struct Stack* const st, int* a) {
  if (st->b == -1) {
    return EMPTY;
  }
  *a = st->s[st->b];
  return OK;
}

int Stack_size(struct Stack* const st, int* a) {
  *a = st->b + 1;
  return OK;
}

int Stack_clear(struct Stack* st) {
  st->b = -1;
  return OK;
}

int Stack_destroy(struct Stack* st) {
  Stack_clear(st);
  free(st->s);
  st->s = NULL;
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
    command[i] = (char) b;
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
    case 'b':
      return BACK;
    case 's':
      return SIZE;
    case 'c':
      return CLEAR;
    default:
      return EXIT;
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  struct Stack st;
  Stack_init(&st);
  enum Operation op;
  int buf;
  int ret;
  do {
    op = get_operation();
    switch (op) {
      case PUSH:
        scanf("%d", &buf);
        ret = Stack_push(&st, buf);
        break;
      case POP:
        ret = Stack_pop(&st, &buf);
        break;
      case BACK:
        ret = Stack_back(&st, &buf);
        break;
      case SIZE:
        ret = Stack_size(&st, &buf);
        break;
      case CLEAR:
        ret = Stack_clear(&st);
        break;
      case EXIT:
        ret = Stack_destroy(&st);
        break;
      default:
        return 0;
    }
    if (ret == OK) {
      if (op == BACK || op == SIZE || op == POP) {
        printf("%d\n", buf);
      } else if (op == EXIT) {
        printf("bye\n");
      } else {
        printf("ok\n");
      }
    } else if (ret == MEM_ERROR) {
      return 2;
    } else {
      printf("error\n");
    }
  } while (op != EXIT);
  
  return 0;
}

