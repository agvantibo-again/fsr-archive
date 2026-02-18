#include <stdio.h>
#include <stdlib.h> // malloc(), free()
#include <stdbool.h>

#define HEAPQ_CAP_INIT 2

enum Operation {
  HALT,
  INSERT,
  EXTRACT,
  IS_EMPTY,
  EDIT,
};

enum RetCode {
  OK,
  EMPTY,
  NOTFOUND,
  MEM_ERROR
};

struct kv {
  int key;
  long double value;
};

struct HeapQ {
  size_t len, cap;
  struct kv* tree;
};

enum RetCode HeapQ_init(struct HeapQ* hq);
enum RetCode HeapQ_insert(struct HeapQ* hq, struct kv const val);
enum RetCode HeapQ_extract(struct HeapQ* hq, struct kv* const val);
enum RetCode HeapQ_peek(struct HeapQ* hq, struct kv* const val);
enum RetCode HeapQ_empty(struct HeapQ* hq, bool* flag);
enum RetCode HeapQ_sift_down(struct HeapQ* hq, size_t const at);
enum RetCode HeapQ_sift_up(struct HeapQ* hq, size_t const at);
enum RetCode HeapQ_edit(struct HeapQ* hq, int const key, long double const val);
void HeapQ_zap(struct HeapQ* hq);

inline static void swap_kv(struct kv* i, struct kv* j) {
  struct kv k = *i;
  *i = *j;
  *j = k;
}

enum RetCode HeapQ_init(struct HeapQ* hq) {
  hq->len = 0;
  hq->cap = HEAPQ_CAP_INIT;
  hq->tree = malloc(HEAPQ_CAP_INIT * sizeof(struct kv));
  return (hq->tree) ? OK : MEM_ERROR;
}

enum RetCode HeapQ_insert(struct HeapQ* hq, struct kv const val) {
  ++hq->len;
  if (hq->len == hq->cap) {
    size_t const new_cap = hq->cap * 2;
    struct kv* new_tree = realloc(hq->tree, new_cap * sizeof(struct kv));
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

enum RetCode HeapQ_extract(struct HeapQ* hq, struct kv* const val) {
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

enum RetCode HeapQ_peek(struct HeapQ* hq, struct kv* const val) {
  if (!hq->len) {
    return EMPTY;
  }
  *val = hq->tree[0];
  return OK;
}

enum RetCode HeapQ_empty(struct HeapQ* hq, bool* flag) {
  if (!hq) {
    return MEM_ERROR;
  }
  *flag = (hq->len <= 0);
  return OK;
} 

enum RetCode HeapQ_edit(struct HeapQ* hq, int const val_0, long double const val) {
  size_t at;
  for (at = 0; (at 
    < hq->len && hq->tree[at].key != val_0); ++at) {}
  if (at == hq->len) { // unsuccessful search
    return NOTFOUND;
  }
  struct kv old = hq->tree[at];
  hq->tree[at].value = val;
  if (val > old.value) {
    HeapQ_sift_up(hq, at); // bubble up greater value
  } else {
    HeapQ_sift_down(hq, at); // sink down lesser value
  }
  return OK;
}

enum RetCode HeapQ_sift_down(struct HeapQ* hq, size_t const at) {
  size_t min = at;
  size_t left = at * 2 + 1;
  size_t right = at * 2 + 2;

  if (left < hq->len && hq->tree[left].value >= hq->tree[min].value) {
    min = left;
  }
  if (right < hq->len && hq->tree[right].value > hq->tree[min].value) {
    min = right;
  }
  if (min != at) {
    swap_kv(hq->tree + at, hq->tree + min);
    return HeapQ_sift_down(hq, min);
  }
  return OK;
}

enum RetCode HeapQ_sift_up(struct HeapQ* hq, size_t at) {
  while (at != 0 && hq->tree[(at - 1) / 2].value < hq->tree[at].value) {
    swap_kv(hq->tree + at, hq->tree + ((at - 1) / 2));
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
  // int b1, b2;
  struct kv b_kv;
  bool empty = true;
  do {
    scanf("%d", &op);
    switch (op) {
      case HALT:
        ret = OK;
        break;
      case INSERT:
        scanf("%d %Lf", &b_kv.key, &b_kv.value);
        ret = HeapQ_insert(hq, b_kv);
        break;
      case EXTRACT:
        ret = HeapQ_extract(hq, &b_kv);
        break;
      case IS_EMPTY:
        ret = HeapQ_empty(hq, &empty);
        break;
      case EDIT:
        scanf("%d %Lf", &b_kv.key, &b_kv.value);
        ret = HeapQ_edit(hq, b_kv.key, b_kv.value);
        break;
      default:
        exit(NOTFOUND);
    }
    switch(ret) {
      case OK:
        if (op == EXTRACT) { printf("%d %Lf\n", b_kv.key, b_kv.value); }
        else if (op == IS_EMPTY) { printf("%d\n", empty); }
        break;
      case EMPTY:
        printf("The P_queue is empty\n");
        break;
      case NOTFOUND:
        printf("Not found\n");
        break;
      case MEM_ERROR:
        EXIT(MEM_ERROR);
    }
  } while (op != HALT);
  EXIT(OK);
}
