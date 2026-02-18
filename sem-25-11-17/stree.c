
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct BTNode {
  int val;
  struct BTNode *l, *r;
};

enum Operations {
  HALT,
  INSERT,
  SEARCH,
  DELETE,
};

struct BTNode* bt_insert(struct BTNode** root_ptr, int const a) {
  if (!root_ptr) {
    return NULL;
  }
  struct BTNode* new_node = malloc(sizeof(struct BTNode));
  struct BTNode* root = *root_ptr;
  if (!new_node) {
    return new_node;
  }
  new_node->val = a;
  new_node->l = new_node->r = NULL;
  if (!root) {
    *root_ptr = new_node;
    return new_node;
  }
  struct BTNode* curr = root;
  bool right_ok = false, left_ok = false;
  do {
    right_ok = (a < curr->val && curr->l != NULL);
    left_ok = (a >= curr->val && curr->r != NULL);
    if (right_ok) {curr = curr->l;}
    else if (left_ok) {curr = curr->r;}
  } while (curr != NULL && (right_ok || left_ok));
  if (a < curr->val) {curr->l = new_node;}
  else {curr->r = new_node;}
  return root;
}

struct BTNode const* bt_search(struct BTNode const* root, int const a) {
  while (root) {
    if (root->val == a) {
      return root;
    } else if (a < root->val) { root = root->l; }
    else { root = root->r; }
  }
  return NULL;
}

struct BTNode* bt_delete(struct BTNode* root, int const a) {
  if (!root) {
    return 0;
  }
  if (root->val > a) {
    root->l = bt_delete(root->l, a);
  } else if (root->val < a) {
    root->r = bt_delete(root->r, a);
  } else {
    struct BTNode* temp;
    if (!root->l) {
      temp = root->r;
      free(root);
      return temp;
    }
    if (!root->r) {
      temp = root->l;
      free(root);
      return temp;
    }
    temp = root->r;
    while (temp != NULL && temp->l != NULL) {
      temp = temp->l;
    }
    root->val = temp->val;
    root->r = bt_delete(root->r, temp->val);
  }
  return root;
}

void bt_free(struct BTNode* root) {
  if (!root) {return;}
  bt_free(root->l);
  bt_free(root->r);
  if (!root->r && !root->l) {free(root);}
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  enum Operations op;
  int buf;
  int scanr;
  struct BTNode* tree = NULL;
  struct BTNode const* tmp;
  do {
    scanr = scanf("%d", &op);
    if (scanr == EOF) {return 0;}
    if (op != HALT) {
      scanf("%d", &buf);
      switch (op) {
        case INSERT:
          tmp = bt_insert(&tree, buf);
          break;
        case SEARCH:
          tmp = bt_search(tree, buf);
          break;
        case DELETE:
          tmp = bt_delete(tree, buf);
          break;
        default:
          return 112;
      }
      buf = (tmp != NULL);
      printf("%d\n", buf);
    }
  } while (op != HALT);

  return 0;
}

