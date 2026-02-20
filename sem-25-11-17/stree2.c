
#include <stdio.h>
#include <stdlib.h>

struct BTNode {
  int val;
  struct BTNode *l, *r;
};

enum Operations { HALT, INSERT, DELETE, DISPLAY, CLEAR };

struct BTNode *bt_insert(struct BTNode **root_ptr, int const a) {
  struct BTNode *new_node = malloc(sizeof(struct BTNode));
  struct BTNode *root = *root_ptr;
  if (!new_node) {
    return new_node;
  }
  new_node->val = a;
  new_node->l = new_node->r = NULL;
  if (!root) {
    *root_ptr = new_node;
    return new_node;
  }
  struct BTNode *curr = root;
  while (curr != NULL) {
    if (a < curr->val && curr->l != NULL) {
      curr = curr->l;
    } else if (a >= curr->val && curr->r != NULL) {
      curr = curr->r;
    } else
      break;
  }
  if (a < curr->val) {
    curr->l = new_node;
  } else {
    curr->r = new_node;
  }
  return root;
}

struct BTNode const *bt_search(struct BTNode const *root, int const a) {
  while (root) {
    if (root->val == a) {
      return root;
    } else if (a < root->val) {
      root = root->l;
    } else {
      root = root->r;
    }
  }
  return NULL;
}

struct BTNode *bt_delete(struct BTNode *root, int const a) {
  if (!root) {
    return 0;
  }
  if (root->val > a) {
    root->l = bt_delete(root->l, a);
  } else if (root->val < a) {
    root->r = bt_delete(root->r, a);
  } else {
    struct BTNode *temp;
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

void bt_free(struct BTNode *root) {
  if (!root) {
    return;
  }
  bt_free(root->l);
  bt_free(root->r);
  if (!root->r && !root->l) {
    free(root);
  }
}

void bt_inorder(struct BTNode *root) {
  if (!root) {
    return;
  }
  bt_inorder(root->l);
  printf("%d ", root->val);
  bt_inorder(root->r);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  enum Operations op;
  int buf;
  struct BTNode *tree = NULL;
  do {
    scanf("%d", &op);
    if (op == INSERT || op == DELETE) {
      scanf("%d", &buf);
    }
    switch (op) {
    case INSERT:
      bt_insert(&tree, buf);
      break;
    case DELETE:
      bt_delete(tree, buf);
      break;
    case DISPLAY:
      bt_inorder(tree);
      putchar('\n');
      break;
    case CLEAR:
      bt_free(tree);
      tree = NULL;
      break;
    case HALT:
      break;
    }
  } while (op != HALT);

  return 0;
}
