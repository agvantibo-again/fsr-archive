#include <stdbool.h> // bool, true, false
#include <stdio.h>   // scanf(), printf()
#include <stdlib.h>  // malloc(), free(), qsort()

typedef unsigned long ul;

struct SetSystem {
  size_t len;
  ul *parent;
  ul *size;
};

struct Edge {
  long weight;
  ul from;
  ul to;
};

static inline void swap(ul *a, ul *b) {
  ul const c = *a;
  *a = *b;
  *b = c;
}

bool ss_init(struct SetSystem *ss, ul const len) {
  ss->parent = malloc(sizeof(ul) * len);
  ss->size = malloc(sizeof(ul) * len);
  ss->len = len;
  if (!ss->parent || !ss->size) {
    return false;
  }
  return true;
}

ul find_set(struct SetSystem *ss, ul const v) {
  if (v == ss->parent[v])
    return v;
  return ss->parent[v] = find_set(ss, ss->parent[v]);
}

void make_set(struct SetSystem *ss, ul const v) {
  ss->parent[v] = v;
  ss->size[v] = 1;
}

void union_sets(struct SetSystem *ss, ul a, ul b) {
  a = find_set(ss, a);
  b = find_set(ss, b);
  if (a != b) {
    if (ss->size[a] < ss->size[b])
      swap(&a, &b);
    ss->parent[b] = a;
    ss->size[a] += ss->size[b];
  }
}

void ss_zap(struct SetSystem *ss) {
  free(ss->parent);
  free(ss->size);
  ss->len = 0;
}

int Edge_compare(void const *a, void const *b) {
  long diff =
      (((struct Edge const *)a)->weight - ((struct Edge const *)b)->weight);
  return (diff > 0) - (diff < 0);
}

int main(void) {
  ul N, M;
  scanf("%lu%lu", &N, &M);
  if (M < 1 || N < 1) {
    return 1;
  }
  struct SetSystem dsu;
  if (!ss_init(&dsu, N)) {
    ss_zap(&dsu);
    return 1;
  }
  for (ul i = 0; i < N; ++i) {
    make_set(&dsu, i);
  }
  struct Edge edges[M];
  for (ul i = 0; i < M; ++i) { // ingest edges
    scanf("%lu%lu%ld", &edges[i].from, &edges[i].to, &edges[i].weight);
    --edges[i].from;
    --edges[i].to;
  }

  qsort(edges, M, sizeof(struct Edge), Edge_compare);
  long total_weight = 0;
  for (ul i = 0; i < M; ++i) {
    if (find_set(&dsu, edges[i].from) != find_set(&dsu, edges[i].to)) {
      union_sets(&dsu, edges[i].from, edges[i].to);
      total_weight += edges[i].weight;
    }
  }
  printf("%lu\n", total_weight);

  ss_zap(&dsu);
  return 0;
}