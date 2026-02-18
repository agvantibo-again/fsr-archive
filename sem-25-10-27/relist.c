// relist.c
#include <stdio.h>  // scanf(), printf(), putchar()
#include <stdlib.h> // malloc(), free()

enum RetCode {
  OK,
  EMPTY, // reserved,
  MEM_ERROR
};

struct ListItem {
  double val;
  struct ListItem *ptr;
};

// const tries to apply itself to the nearest left operand, and if there's none
// it applies to the nearest right instead

// struct const * is a mutable pointer to a immutable struct
// struct* const is a constant pointer
// struct const * const is a functional programmer's idea of awesome

enum RetCode lst_append(struct ListItem **head, double const val) {
  struct ListItem *new_item = malloc(sizeof(struct ListItem));
  if (!new_item) {
    return MEM_ERROR;
  }
  new_item->val = val;
  new_item->ptr = NULL;
  if (!*head) { // list was empty
    *head = new_item;
  } else {
    struct ListItem *last = *head;
    while (last->ptr) {
      last = last->ptr;
    }
    last->ptr = new_item;
  }
  return OK;
}

enum RetCode lst_prepend(struct ListItem **head, double const val) {
  struct ListItem *new_item = malloc(sizeof(struct ListItem));
  if (!new_item) {
    return MEM_ERROR;
  }
  new_item->val = val;
  new_item->ptr = *head;
  *head = new_item;
  return OK;
}

enum RetCode lst_print(struct ListItem const *head) {
  char *fmt;
  while (head) {
    fmt = (!head->ptr) ? "%lf" : "%lf, ";
    printf(fmt, head->val);
    head = head->ptr;
  }
  putchar('\n');
  return OK;
}

int lst_copy(struct ListItem const *head, struct ListItem **new_head) {
  *new_head = NULL;
  int Σret = 0;
  while (head) {
    Σret += lst_append(new_head, head->val);
    head = head->ptr;
  }
  // return (Σret) ? MEM_ERROR : OK;
  return Σret;
}

void lst_destroy(
    struct ListItem *head) { // unused. the OS would take care of that
  struct ListItem *tmp;
  while (head) {
    tmp = head->ptr;
    free(head);
    head = tmp;
  }
}

int main(void) {
  double buf;
  struct ListItem *l1, *l2;
  l1 = l2 = NULL;
  scanf("%lf", &buf);
  while (buf > 0) {
    lst_prepend(&l1, buf);
    scanf("%lf", &buf);
  };
  lst_copy(l1, &l2);
  lst_print(l1);
  lst_print(l2);

  return 0;
}
