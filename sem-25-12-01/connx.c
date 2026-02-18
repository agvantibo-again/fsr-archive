#include <stdio.h> // scanf(), putchar()
#include <stdlib.h> // malloc()
#include <stdbool.h> // bool, true, false

struct SetSystem {
  size_t* parent;
  size_t* size;
};

static inline void swap(size_t* a, size_t* b) {
  size_t const c = *a;
  *a = *b;
  *b = c;
}

bool ss_init(struct SetSystem* ss, size_t l) {
  ss->parent = malloc(sizeof(size_t) * l);
  ss->size = malloc(sizeof(size_t) * l);
  if (!ss->parent || !ss->size) {
    return false;
  }
  return true;
}

size_t find_set(struct SetSystem* ss, size_t v) {
    if (v == ss->parent[v])
        return v;
    return ss->parent[v] = find_set(ss, ss->parent[v]);
}

void make_set(struct SetSystem* ss, size_t v) {
    ss->parent[v] = v;
    ss->size[v] = 1;
}

void union_sets(struct SetSystem* ss, size_t a, size_t b) {
    a = find_set(ss, a);
    b = find_set(ss, b);
    if (a != b) {
        if (ss->size[a] < ss->size[b])
            swap(&a, &b);
        ss->parent[b] = a;
        ss->size[a] += ss->size[b];
    }
}

void ss_zap(struct SetSystem* ss) {
  free(ss->parent);
  free(ss->size);
}

static inline void gen_huge_matrix(size_t size, long long mat[size][size]) {
  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      mat[i][j] = 0;
    }
  }
}

#define ADRENALINE 1000

// int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
int main(void) {
  size_t v = ADRENALINE;
  // scanf("%lu", &v);
  long long mat[ADRENALINE][ADRENALINE];
  gen_huge_matrix(ADRENALINE, mat);

  struct SetSystem ss;
  if (!ss_init(&ss, v * 2)) {
    ss_zap(&ss);
    return 2;
  }

  // Every node is adjacent to itself
  for (size_t i = 0; i < v; ++i) {
    make_set(&ss, i);
  }

  // Ingest adjacence matrix
  for (size_t v1 = 0; v1 < v; ++v1) {
    for (size_t v2 = 0; v2 < v; ++v2) {
      if (mat[v1][v2]) { union_sets(&ss, v1, v2); }
    }
  }

  // If adjacent, this should print the same root v times
  bool conn;
  for (
      size_t i = 1;
      (i < v && (conn = (find_set(&ss, i-1) == find_set(&ss, i))));
      ++i
    ) {
    // printf(
    //   "%lu -> %lu, %lu -> %lu\n",
    //   i-1, find_set(&ss, i-1), i,
    //   find_set(&ss, i)
    // );
  } // a monster
  (conn) ? putchar('1') : putchar('0');
  putchar('\n');

  ss_zap(&ss);
  return 0;
}
