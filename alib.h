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
