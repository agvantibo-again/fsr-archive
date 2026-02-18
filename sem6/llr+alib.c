#ifndef ALIB_C
#define ALIB_C
#include <stdlib.h>
#include <stddef.h>

typedef struct ListNode {
  // Embeddable list component
  struct ListNode *prev;
  struct ListNode *next;
} ListNode;

typedef struct IntList {
  ListNode li;
  int value;
} IntList;

#define LIST_FOREACH(head, node) \
  for (ListNode * node = (head); node != NULL; node = node -> next)
// Iterate over a list

#define EXSTRUCT(ptr, typename, member) \
  (typename*)((char*)ptr - offsetof(typename, member))
// Get a pointer to mother struct

void list_init(ListNode* head);
void list_append(ListNode* head, ListNode* node);
void list_remove(ListNode* node);
size_t list_len(ListNode const * head);

#endif // ALIB_C
#ifndef ALIB_C
#include "alib.h"
#endif // the double include guard is needed for concatenation

void list_init(ListNode* head) {
  head->prev = head->next = NULL;
}

void list_append(ListNode* head, ListNode* node) {
  ListNode* inode = head;
  while (inode->next != NULL) {
    inode = inode->next;
  }
  inode->next = node;
  node->prev = inode;
  node->next = NULL; 
}

void list_remove(ListNode* node) {
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  node->prev = NULL;
  node->next = NULL;
}

size_t list_len(ListNode const * head) {
  size_t len = 1;
  ListNode const * inode = head;
  while (inode->next != NULL) {
    inode = inode->next;
    len++;
  }
  
  return len;
}

#include <stdio.h>

#ifndef ALIB_C
#include "alib.h"
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n;
  scanf("%d", &n);

  IntList* start = malloc(sizeof(IntList));
  list_init(&start->li);
  scanf("%d", &start->value);

  IntList* new_item = start;
  for (int i = 1; i < n; ++i) {
    new_item = malloc(sizeof(IntList));
    list_init(&new_item->li); 
    scanf("%d", &new_item->value);
    list_append(&start->li, &new_item->li);
  }

  LIST_FOREACH(&start->li, elem_i) {
    printf("%d; ", (EXSTRUCT(elem_i, IntList, li))->value);
  }

  return 0;
}
