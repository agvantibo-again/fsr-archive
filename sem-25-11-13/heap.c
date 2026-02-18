#include <stdio.h>
#include <stdlib.h> // malloc(), free()

#define HEAPQ_CAP_INIT 2

enum Operation {
  HALT,
  INSERT,
  PEEK,
  EXTRACT,
  EDIT,
};

enum RetCode {
  OK,
  EMPTY,
  NOTFOUND,
  MEM_ERROR
};

struct HeapQ {
  size_t len, cap;
  int* tree;
};

enum RetCode HeapQ_init(struct HeapQ* hq);
enum RetCode HeapQ_insert(struct HeapQ* hq, int const val);
enum RetCode HeapQ_extract(struct HeapQ* hq, int* val);
enum RetCode HeapQ_peek(struct HeapQ* hq, int* val);
enum RetCode HeapQ_sift_down(struct HeapQ* hq, size_t const at);
enum RetCode HeapQ_sift_up(struct HeapQ* hq, size_t at);
enum RetCode HeapQ_edit(struct HeapQ* hq, size_t const at, int const val);
void HeapQ_zap(struct HeapQ* hq);

inline static void swap(int* i, int* j) {
  int k = *i;
  *i = *j;
  *j = k;
}

enum RetCode HeapQ_init(struct HeapQ* hq) {
  hq->len = 0;
  hq->cap = HEAPQ_CAP_INIT;
  hq->tree = malloc(sizeof(int) * hq->cap);
  return (hq->tree) ? OK : MEM_ERROR;
};
enum RetCode HeapQ_insert(struct HeapQ* hq, int const val) {
  if (hq->len + 1 == hq->cap) {
    size_t new_cap = hq->cap * 2;
    int* new_tree = realloc(hq->tree, new_cap * sizeof(int));
    if (!new_tree) {
      return MEM_ERROR;
    }
    hq->cap = new_cap;
    hq->tree = new_tree;
  }
  hq->tree[hq->len++] = val;
  return OK;
};
enum RetCode HeapQ_extract(struct HeapQ* hq, int* val) {
  if (!hq->len) {
    return EMPTY;
  } // else
  if (hq->len == 1) {
    *val = hq->tree[--hq->len];
    return OK;
  } // else
  *val = hq->tree[0];
  hq->tree[0] = hq->tree[--hq->len];
  HeapQ_sift_down(hq, 0);
  return OK;
}
enum RetCode HeapQ_peek(struct HeapQ* hq, int* val) {
  if (!hq->len) {
    return EMPTY;
  }
  *val = hq->tree[0];
  return OK;
};
enum RetCode HeapQ_sift_down(struct HeapQ* hq, size_t const at) {
  int left = at * 2 + 1;
  int right = at * 2 + 2;
  int tgt = at; // max child
  if (left <= hq->len && hq->tree[left] > hq->tree[at]) {
    tgt = left;
  }
  if (right <= hq->len && hq->tree[right] > hq->tree[tgt]) {
    tgt = right;
  }
  if (tgt != at) {
    swap(&hq->tree[tgt], &hq->tree[at]);
    HeapQ_sift_down(hq, tgt);
  }
}
enum RetCode HeapQ_sift_up(struct HeapQ* hq, size_t at) {
  if (at >= hq->len) {
    return NOTFOUND;
  }
  if (!hq->len) {
    return EMPTY;
  }
  while (at != 0 && hq->tree[(at - 1) / 2] > hq->tree[at]) {
    swap(&hq->tree[at], &hq->tree[ (at-1)/2 ]);
    at = (at - 1) / 2;
  }
  return OK;
}
enum RetCode HeapQ_edit(struct HeapQ* hq, size_t const at, int const val) {
  if (at >= hq->len) {
    return NOTFOUND;
  }
  if (!hq->len) {
    return EMPTY;
  }
  int old = hq->tree[at];
  hq->tree[at] = val;
  if (val > old) { // sink
    HeapQ_sift_down(hq, at);
  } else if (val < old) {         // float
    HeapQ_sift_up(hq, at);
  }
  return OK;
};
void HeapQ_zap(struct HeapQ* hq) {
  free(hq->tree);
  hq->cap = 0;
};

int main(void) {
  enum Operation op
}
