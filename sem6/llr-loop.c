#include <stdio.h>
#include <stdlib.h>

typedef struct IntListML {
  int val;
  struct IntListML* next;
} IntListML;

IntListML* reverse_IntListML(IntListML* head) {
  IntListML *curr = head, *prev = NULL, *next;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  return prev;
}

void print_IntListML(IntListML* node) {
  while (node != NULL) {
    printf("%d", node->val);
    if (node->next != NULL) {
      printf("; ");
    }
    node = node->next;
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
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
  
  print_IntListML(reverse_IntListML(&head));

  putchar('\n');

  // free(NULL);
  return 0;
}
