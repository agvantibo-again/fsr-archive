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
enum RetCode HeapQ_sift_up(struct HeapQ* hq, size_t const at);
enum RetCode HeapQ_edit(struct HeapQ* hq, int const val_0, int const val);
void HeapQ_zap(struct HeapQ* hq);

inline static void swap(int* i, int* j) {
  int k = *i;
  *i = *j;
  *j = k;
}

enum RetCode HeapQ_init(struct HeapQ* hq) {
  hq->len = 0;
  hq->cap = HEAPQ_CAP_INIT;
  hq->tree = malloc(HEAPQ_CAP_INIT * sizeof(int));
  return (hq->tree) ? OK : MEM_ERROR;
}

enum RetCode HeapQ_insert(struct HeapQ* hq, int const val) {
  ++hq->len;
  if (hq->len == hq->cap) {
    size_t const new_cap = hq->cap * 2;
    int* new_tree = realloc(hq->tree, new_cap * sizeof(int));
    if (!new_tree) {
      return MEM_ERROR;
    }
    hq->cap = new_cap;
    hq->tree = new_tree;
  }
  size_t i = hq->len - 1;
  hq->tree[i] = val;
  HeapQ_sift_up(hq, i);
  return OK;
}

enum RetCode HeapQ_extract(struct HeapQ* hq, int* val) {
  if (!hq->len) {
    return EMPTY;
  }
  if (hq->len == 1) {
    --hq->len;
    *val = hq->tree[0];
    return OK;
  }
  *val = hq->tree[0];
  hq->tree[0] = hq->tree[hq->len - 1];
  --hq->len;
  HeapQ_sift_down(hq, 0);
  return OK;
}

enum RetCode HeapQ_peek(struct HeapQ* hq, int* val) {
  if (!hq->len) {
    return EMPTY;
  }
  *val = hq->tree[0];
  return OK;
}

enum RetCode HeapQ_edit(struct HeapQ* hq, int const val_0, int const val) {
  size_t at;
  for (at = 0; (at < hq->len && hq->tree[at] != val_0); ++at) {}
  if (at == hq->len) { // unsuccessful search
    return NOTFOUND;
  }
  int old = hq->tree[at];
  hq->tree[at] = val;
  if (val < old) {
    HeapQ_sift_up(hq, at); // bubble up lesser value
  } else {
    HeapQ_sift_down(hq, at); // sink down greater value
  }
  return OK;
}

enum RetCode HeapQ_sift_down(struct HeapQ* hq, size_t const at) {
  size_t min = at;
  size_t left = at * 2 + 1;
  size_t right = at * 2 + 2;

  if (left < hq->len && hq->tree[left] < hq->tree[min]) {
    min = left;
  }
  if (right < hq->len && hq->tree[right] < hq->tree[min]) {
    min = right;
  }
  if (min != at) {
    swap(hq->tree + at, hq->tree + min);
    return HeapQ_sift_down(hq, min);
  }
  return OK;
}

enum RetCode HeapQ_sift_up(struct HeapQ* hq, size_t at) {
  while (at != 0 && hq->tree[(at - 1) / 2] > hq->tree[at]) {
    swap(hq->tree + at, hq->tree + ((at - 1) / 2));
    at = (at - 1) / 2;
  }
  return OK;
}

void HeapQ_zap(struct HeapQ* hq) {
  free(hq->tree);
  hq->tree = NULL;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  #define EXIT(n) HeapQ_zap(hq); free(hq); return n;
  struct HeapQ* hq = malloc(sizeof(struct HeapQ));
  if (!hq) {return 2;}
  if (HeapQ_init(hq) == MEM_ERROR) {return 2;};
  enum Operation op;
  enum RetCode ret;
  int b1, b2;
  do {
    scanf("%d", &op);
    switch (op) {
      case HALT:
        ret = OK;
        break;
      case INSERT:
        scanf("%d", &b1);
        ret = HeapQ_insert(hq, b1);
        break;
      case PEEK:
        ret = HeapQ_peek(hq, &b1);
        break;
      case EXTRACT:
        ret = HeapQ_extract(hq, &b1);
        break;
      case EDIT:
        scanf("%d%d", &b1, &b2);
        ret = HeapQ_edit(hq, b1, b2);
        break;
      default:
        return 1;
    }
    switch(ret) {
      case OK:
        if (op == PEEK || op == EXTRACT) { printf("%d\n", b1); }
        break;
      case EMPTY:
        printf("Heap is empty\n");
        break;
      case NOTFOUND:
        printf("Not found\n");
        break;
      case MEM_ERROR:
        EXIT(2);
    }
  } while (op != HALT);
  EXIT(0)
}
