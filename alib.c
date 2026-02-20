#ifndef ALIB_C
#include "alib.h"
#endif // the double include guard is needed for concatenation

void list_init(ListNode *head) { head->prev = head->next = NULL; }

void list_append(ListNode *head, ListNode *node) {
  ListNode *inode = head;
  while (inode->next != NULL) {
    inode = inode->next;
  }
  inode->next = node;
  node->prev = inode;
  node->next = NULL;
}

void list_remove(ListNode *node) {
  if (node->prev != NULL) {
    node->prev->next = node->next;
  }
  if (node->next != NULL) {
    node->next->prev = node->prev;
  }
  node->prev = NULL;
  node->next = NULL;
}

size_t list_len(ListNode const *head) {
  size_t len = 1;
  ListNode const *inode = head;
  while (inode->next != NULL) {
    inode = inode->next;
    len++;
  }

  return len;
}
