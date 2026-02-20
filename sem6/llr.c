#include <stdio.h>
#include <stdlib.h>

typedef struct IntListML {
  int val;
  struct IntListML *next;
} IntListML;

void print_IntListML(IntListML *head, int d) {
  if (head->next != NULL) {
    print_IntListML(head->next, d + 1);
  }
  printf("%d", head->val);
  if (d != 0) {
    printf("; ");
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n);

  IntListML head;
  scanf("%d", &head.val);

  IntListML *cur;
  cur = &head;
  for (int i = 1; i < n; ++i) {
    cur->next = malloc(sizeof(IntListML));
    scanf("%d", &cur->next->val);
    cur = cur->next;
  }
  cur->next = NULL;
  print_IntListML(&head, 0);
  putchar('\n');

  return 0;
}
