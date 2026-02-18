
#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>

enum Operations {
  HALT = 0,
  PUSH_FRONT = 1,
  PUSH_BACK = 2,
  POP_FRONT = 3,
  POP_BACK = 4,
  FRONT = 5,
  BACK = 6,
  IS_EMPTY = 7,
  CLEAR = 8
};

enum RetCodes {
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

int is_Deque_empty(struct Deque* const d) {
  return (d->ft == NULL);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  enum Operations op;
  int buf, ret;
  struct Deque d;
  Deque_init(&d);
  do {
    scanf("%d", &op);
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
    case IS_EMPTY:
      ret = is_Deque_empty(&d);
      break;
    case CLEAR:
      ret = Deque_clear(&d);
      break;
    default:
      ret = 0;
      break;
    }
    if (ret == 2) {
      Deque_clear(&d);
      return 1;
    } else if (op == IS_EMPTY) {
        printf("%d\n", ret);
    } else if (ret == 1) {
      printf("Deque is empty\n");
    } else if (op == POP_FRONT || op == POP_BACK || op == FRONT || op == BACK) {
      printf("%d\n", buf);
    }
  } while (op != 0);

  Deque_clear(&d);
  return 0;
}
