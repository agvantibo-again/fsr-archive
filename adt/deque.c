
#include <stdio.h>
#include <stdlib.h> // malloc(), free()
#include <string.h> // strtok_r()

#define COMMAND_MAX_LENGTH 32
#define IS_ALPHA(ch) ('A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z')

enum Operation {
  EXIT = 0,
  PUSH_FRONT = 1,
  PUSH_BACK = 2,
  POP_FRONT = 3,
  POP_BACK = 4,
  FRONT = 5,
  BACK = 6,
  SIZE = 7,
  CLEAR = 8,
  FAILURE = 128,
};

enum RetCode {
  OK = 0,
  EMPTY = 1,
  MEM_ERROR = 2
};

struct ListItem {
  int v;
  struct ListItem *p, *n;
};

struct Deque {
  struct ListItem *ft, *bk;
};

int Deque_init(struct Deque* d)
{
  d->ft = d->bk = NULL;
  return OK;
}

int Deque_push_back(struct Deque* d, int const a) {
  struct ListItem* new = malloc(sizeof(struct ListItem));
  if (new == NULL) {
    return MEM_ERROR;
  }
  new->v = a;
  if (d->bk == NULL) {
    d->ft = d->bk = new;
    d->bk->p = d->bk->n = NULL;
  } else {
    new->n = d->bk;
    d->bk->p = new;
    new->p = NULL;
    d->bk = new;
  }
  return OK;
}

int Deque_push_front(struct Deque* d, int const a) {
  struct ListItem* new = malloc(sizeof(struct ListItem));
  if (new == NULL) {
    return MEM_ERROR;
  }
  new->v = a;
  if (d->ft == NULL) {
    d->bk = d->ft = new;
    d->ft->p = d->ft->n = NULL;
  } else {
    new->p = d->ft;
    d->ft->n = new;
    new->n = NULL;
    d->ft = new;
  }
  return OK;
}

int Deque_back(struct Deque* const d, int* a) {
  if (d->ft == NULL) {
    return EMPTY;
  }
  *a = d->bk->v;
  return OK;
}

int Deque_front(struct Deque* const d, int* a) {
  if (d->ft == NULL) {
    return EMPTY;
  }
  *a = d->ft->v;
  return OK;
}

int Deque_pop_back(struct Deque* d, int* a) {
  if (d->bk == NULL) {
    return EMPTY;
  }
  *a = d->bk->v;
  if (d->bk->n == NULL) {
    free(d->bk);
    d->bk = d->ft = NULL;
  } else {
    d->bk = d->bk->n;
    free(d->bk->p);
    d->bk->p = NULL;
  }
  return OK;
}

int Deque_pop_front(struct Deque* d, int* a) {
  if (d->ft == NULL) {
    return EMPTY;
  }
  *a = d->ft->v;
  if (d->ft->p == NULL) {
    free(d->ft);
    d->ft = d->bk = NULL;
  } else {
    d->ft = d->ft->p;
    free(d->ft->n);
    d->ft->n = NULL;
  }
  return OK;
}

int Deque_clear(struct Deque* d) {
  struct ListItem* i = d->ft;
  while (i != NULL) {
    struct ListItem* tmp = i->p;
    free(i);
    i = tmp;
  }
  d->ft = d->bk = NULL;
  return OK;
}

int Deque_size(struct Deque* const d, int* a) {
  *a = 0;
  struct ListItem* i = d->ft;
  while (i != NULL) {
    ++ *a;
    i = i->p;
  }
  return OK;
}

enum Operation handle_p(char const command[COMMAND_MAX_LENGTH]) {
  char next_code;
  int i;
  for (i = 0; i < COMMAND_MAX_LENGTH && command[i] != '_'; ++i) {};
  if (i + 2 >= COMMAND_MAX_LENGTH) {
    return FAILURE;
  } else {
    next_code = command[i + 1];
    }
    if (command[1] == 'o') { // po
      if (next_code == 'f') {
          return POP_FRONT;
      } else if (next_code == 'b') {
          return POP_BACK;
      } else {
        return FAILURE;
      }
    } else if (command[1] == 'u') {
      if (next_code == 'f') {
          return PUSH_FRONT;
      } else if (next_code == 'b') {
          return PUSH_BACK;
      } else {
        return FAILURE;
      }
    } else {
      return FAILURE;
    }
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
  } while ((IS_ALPHA(b) || b == '_') && i < COMMAND_MAX_LENGTH);

  switch (command[0]) {
    case 'p':
      return handle_p(command);
    case 'f':
      return FRONT;
    case 'b':
      return BACK;
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


// int is_Deque_empty(struct Deque* const d) {
//   return (d->ft == NULL);
// }

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  enum Operation op;
  int buf, ret;
  struct Deque d;
  Deque_init(&d);
  do {
    op = get_operation();
    switch (op) {
    case PUSH_FRONT:
      scanf("%d", &buf);
      ret = Deque_push_front(&d, buf);
      break;
    case PUSH_BACK:
      scanf("%d", &buf);
      ret = Deque_push_back(&d, buf);
      break;
    case POP_FRONT:
      ret = Deque_pop_front(&d, &buf);
      break;
    case POP_BACK:
      ret = Deque_pop_back(&d, &buf);
      break;
    case FRONT:
      ret = Deque_front(&d, &buf);
      break;
    case BACK:
      ret = Deque_back(&d, &buf);
      break;
    case SIZE:
      ret = Deque_size(&d, &buf);
      break;
    case CLEAR:
      ret = Deque_clear(&d);
      break;
    case EXIT:
      ret = Deque_clear(&d);
      break;
    default:
      return 1;
    }
    if (ret == MEM_ERROR) {
      Deque_clear(&d);
      return 2;
    } else if (ret == EMPTY) {
      printf("error\n");
    } else if (
      op == POP_FRONT || op == POP_BACK ||
      op == FRONT || op == BACK ||
      op == SIZE
    ) {
      printf("%d\n", buf);
    } else if (op == EXIT) {
      printf("bye\n");
    } else {
      printf("ok\n");
    }
  } while (op != 0);

  return 0;
}
