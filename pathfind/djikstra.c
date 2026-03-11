#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef unsigned long ul;

ul find_proximal_vex(ul const N, ul const distance[restrict static N],
                     bool const marked[restrict static N]) {
  ul min_distance = ULLONG_MAX;
  ul min_vex = 0;
  for (ul i = 0; i < N; ++i) {
    if (distance[i] < min_distance && !marked[i]) {
      min_vex = i;
      min_distance = distance[i];
    }
  }

  return min_vex;
}

ul minul(ul const a, ul const b) { return (a < b) ? a : b; }

int main(void) {
  ul N, S, F;
  scanf("%lu%lu%lu", &N, &S, &F);
  --S;
  --F;
  long int amat[N][N];

  for (ul r = 0; r < N; ++r) {
    for (ul c = 0; c < N; ++c) {
      scanf("%ld", &amat[r][c]);
    }
  }
  ul distance[N];
  for (ul i = 0; i < N; ++i) {
    distance[i] = ULLONG_MAX;
  }
  distance[S] = 0;

  bool marked[N];
  memset(marked, 0, sizeof marked);

  ul proximal_vex;
  for (ul i = 0; i < N; ++i) {
    proximal_vex = find_proximal_vex(N, distance, marked);
    marked[proximal_vex] = true;
    for (ul dest = 0; dest < N; ++dest) {
      if (amat[proximal_vex][dest] != -1 && !marked[dest]) {
        distance[dest] = minul(distance[dest], distance[proximal_vex] +
                                                   amat[proximal_vex][dest]);
      }
    }
  }
  if (distance[F] == ULLONG_MAX) {
    printf("-1");
  } else {
    printf("%lu", distance[F]);
  }

  putchar('\n');
  return 0;
}
