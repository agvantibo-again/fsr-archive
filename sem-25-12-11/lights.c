#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// #define DEBUG

#ifdef DEBUG
#define DEBUG_TEST 1
#else
#define DEBUG_TEST 0
#endif

#define debug_print(fmt, ...)                                                  \
  do {                                                                         \
    if (DEBUG_TEST)                                                            \
      fprintf(stderr, fmt, __VA_ARGS__);                                       \
  } while (0)

// 𝕍 — number of vertices
// μ — minimal vertex weight

struct Point {
  int x, y;
};

static inline long double distance_euclid(struct Point const a,
                                          struct Point const b) {
  return sqrtl(powl(a.x - b.x, 2) + powl(a.y - b.y, 2));
}

int minweight(int const 𝕍, long double const weight[𝕍], bool const visited[𝕍]) {
  long double min = LDBL_MAX;
  int min_index;

  for (int v = 0; v < 𝕍; ++v) {
    if (visited[v] == false && weight[v] < min) {
      min = weight[v];
      min_index = v;
    }
  }
  return min_index;
}

void prim_MST(int const 𝕍, long double const graph[𝕍][𝕍], int parent[𝕍]) {
  long double weight[𝕍];
  bool visited[𝕍];

  for (int i = 0; i < 𝕍; ++i) {
    weight[i] = LDBL_MAX;
    visited[i] = false;
  }
  weight[0] = 0;
  parent[0] = -1;

  for (int count = 0; count < 𝕍 - 1; ++count) {
    int μ = minweight(𝕍, weight, visited);
    visited[μ] = true;

    for (int v = 0; v < 𝕍; ++v) {
      if ((bool)graph[μ][v] && visited[v] == false && graph[μ][v] < weight[v]) {
        parent[v] = μ;
        weight[v] = graph[μ][v];
      }
    }
  }
}

// void prettyprint_distances(int const 𝕍, long double const graph[𝕍][𝕍]) {
//   for (int v1 = 0; v1 < 𝕍; ++v1) {
//     for (int v2 = v1; v2 < 𝕍; ++v2) {
//       if ((bool) graph[v1][v2]) {
//         printf("%d — %d:\t%Lf\n", v1, v2, graph[v1][v2]);
//       }
//     }
//   }
// }

long double mst_walk(int const 𝕍, long double const graph[𝕍][𝕍],
                     int const parent[𝕍]) {
  // Returns the total MST length
  long double cost = 0;
  for (int i = 1; i < 𝕍; ++i) {
    cost += graph[i][parent[i]];
    debug_print("%d — %d"
                "\t"
                "%Lf"
                "\n",
                parent[i], i, graph[i][parent[i]]);
  }
  return cost;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int w, h, 𝕍;
  scanf("%d %d %d", &w, &h, &𝕍);
  struct Point bulbs[++𝕍];
  bulbs[0].x = bulbs[0].y = 0;
  for (int i = 1; i < 𝕍; ++i) {
    scanf("%d %d", &bulbs[i].x, &bulbs[i].y);
  }

  long double graph[𝕍][𝕍];
  for (int v1 = 0; v1 < 𝕍; ++v1) {
    for (int v2 = 0; v2 < 𝕍; ++v2) {
      if (v1 == v2) {
        graph[v1][v2] = graph[v2][v1] = 0;
      } else {
        graph[v1][v2] = graph[v2][v1] =
            distance_euclid(bulbs[v1], bulbs[v2]) / 100;
      }
    }
  }

  int parent[𝕍];
  prim_MST(𝕍, graph, parent);

  printf("%Lf", 1.5L + mst_walk(𝕍, graph, parent));

  return 0;
}
