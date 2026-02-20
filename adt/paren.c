#include <stdio.h>
#include <stdlib.h>
#define STR(x) #x
#define XSTR(x) STR(x)
#define INPUT_LLIMIT 100000

#ifndef AGV_STACK
#define AGV_STACK

#define STACK_INITIAL_CAP 256
enum RetCode {
  OK = 0,
  NOPE = 1,
  MEM_ERROR = 2,
};

struct Stack {
  int cap;
  int b;
  int *s;
};

int Stack_init(struct Stack *st) {
  st->cap = STACK_INITIAL_CAP;
  st->b = -1;
  st->s = calloc(STACK_INITIAL_CAP, sizeof(int));
  return (st->s != NULL) ? OK : MEM_ERROR;
}

int Stack_push(struct Stack *st, int const a) {
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

int Stack_pop(struct Stack *st, int *a) {
  if (st->b == -1) {
    return NOPE;
  }
  *a = st->s[st->b];
  --st->b;
  return OK;
}

int Stack_back(struct Stack *const st, int *a) {
  if (st->b == -1) {
    return NOPE;
  }
  *a = st->s[st->b];
  return OK;
}

int Stack_size(struct Stack *const st, int *a) {
  *a = st->b + 1;
  return OK;
}

int Stack_clear(struct Stack *st) {
  st->b = -1;
  return OK;
}

int Stack_destroy(struct Stack *st) {
  Stack_clear(st);
  free(st->s);
  st->s = NULL;
  return OK;
}

#endif // AGV_STACK

// full disclosure: i could have not even bothered with the stack
// and just kept a counter of '(' and the solution would be 2x more terse
// and more memory efficient — O(1) vs O(n)
// however this is ADT homework
// also this stack solution could easily be expanded to work with other braces
// so here we go

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  char input[INPUT_LLIMIT + 1];
  scanf("%" XSTR(INPUT_LLIMIT) "s", input);
  // scanf("%100000ms", &input);
  // so there's "%ms" for scanf and it's pretty cool:
  // it takes a char** and does the allocation for you and modifies the pointer
  // therefore i could have ditched the macro kludge entirely and used that,
  // but it's less portable and i've learned about the stringify operator just
  // now and i really wanted to use that
  struct Stack st;
  Stack_init(&st);
  char *cur = input; // decay to pointer to first element
  int oops = 0;
  int val, ret;
  while (*cur) {
    switch (*cur) {
    case '(':
      ret = Stack_push(&st, '(');
      if (ret == MEM_ERROR) {
        goto panic;
      }
      break;
    case ')':
      ret = Stack_back(&st, &val);
      if (ret == NOPE) {
        ++oops;
      } else {
        Stack_pop(&st, &val);
      }
      break;
    default:
      printf("invalid character");
      goto panic;
    }
    ++cur;
  }
  Stack_size(&st, &val);
  printf("%d", oops + val);
  Stack_destroy(&st);
  return OK;

panic:
  Stack_destroy(&st);
  return NOPE;
}
