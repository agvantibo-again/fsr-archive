#include <stdio.h>
#include <stdlib.h>

typedef struct IntListML {
  int val;
  struct IntListML *next;
} IntListML;

void print_IntListML(IntListML *node) {
  while (node != NULL) {
    printf("%d ", node->val);
    node = node->next;
  }
}

void append_IntListML(IntListML *node) {}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  // int buf;
  int n = 0;
  IntListML *head, *cur;
  head = malloc(sizeof(IntListML));
  scanf("%d", &head->val);
  head->next = NULL; // terminate by default

  cur = head;
  while (cur->val != 0) {
    cur->next = malloc(sizeof(IntListML));
    scanf("%d", &cur->next->val);
    cur = cur->next;
    n++;
  };
  cur->next = NULL; // null terminate
  if (n < 2) {      // return early if lists would be empty
    if (n < 1) {
      printf("Empty list\n");
    } else {
      printf("%d\n", head->val);
    }
    printf("Empty list\n");
    return 0;
  }

  IntListML *head_odd, *head_even;
  IntListML *cur_odd, *cur_even;
  cur = head;
  for (int i = 0; i < n && cur != NULL; ++i, cur = cur->next) {
    if (i % 2 == 1) { // odd
    }
  }

  return 0;
}
