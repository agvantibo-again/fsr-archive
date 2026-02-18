
#include <stdlib.h>
#include<stdio.h>


struct BTNode {
  int val;
  struct BTNode *l, *r;
};

enum Operations {
  HALT,
  INSERT,
  NEIGHBOR,
  FREE,
};

struct BTNode* bt_insert(struct BTNode** root_ptr, int const a) {
  struct BTNode* new_node =malloc(sizeof(struct BTNode));
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
  while (curr != NULL) {
    if (a < curr->val && curr->l != NULL) {curr = curr->l;}
    else if (a >= curr->val && curr->r != NULL) {curr = curr->r;}
    else break;
  }
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

struct BTNode const* bt_neighbor(struct BTNode const* root) {
  struct BTNode const* temp = root->l;
  struct BTNode const* ret = NULL;
  while (temp) {
    ret = temp;
    temp = temp->r;
  }
  return ret;
}

struct BTNode* bt_FREE(struct BTNode* root, int const a) {
  if (!root) {
    return 0;
  }
  if (root->val > a) {
    root->l = bt_FREE(root->l, a);
  } else if (root->val < a) {
    root->r = bt_FREE(root->r, a);
  } else {
    struct BTNode*  temp;
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
    root->r = bt_FREE(root->r, temp->val);
  }
  return root;
}

void bt_free(struct BTNode* root) {
  if (!root) {return;}
  bt_free(root->l);
  bt_free(root->r);
  if (!root->r && !root->l) {
    free(root);
  }
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  enum Operations op;
  int buf;
  int scanr;
  struct BTNode* tree = NULL;
  struct BTNode const* tmp;
  struct BTNode const* tgt;
  do {
    scanr = scanf("%d", &op);
    if (scanr == EOF) {return 0;}
    if (op != HALT) {
      if (op != FREE) { scanf("%d", &buf); }
      switch (op) {
        case INSERT:
          tmp = bt_insert(&tree, buf);
          break;
        case NEIGHBOR:
          tgt = bt_search(tree, buf);
          if (!tgt) { printf("The entered value is not stored in the tree\n"); }
          else {
            tmp = bt_neighbor(tgt);
            if (!tmp) { printf("The entered value is minimal\n"); }
            else { printf("%d\n", tmp->val); };
          }
          break;
        case FREE:
          bt_free(tree);
          tree = NULL;
          break;
        default:
          return 112;
      }
      buf = (tmp != NULL);
//      printf("%d\n", buf);
    }
  } while (op != HALT);

  return 0;
}

