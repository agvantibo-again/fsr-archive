#include<stdio.h> // scanf(), printf(), putchar()

#define NONE -2.0

// int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
int main(void) {
  int v, e;
  scanf("%d%d", &v, &e);
  double imat[v][e];
  double amat[v][v];

  for (int edge = 0; edge < e; ++edge) {
    for (int vert = 0; vert < v; ++vert) { // line -> column
      scanf("%lf", &imat[vert][edge]); // you're going to complain about this
      // scanf("%lf", ((double*) imat + vert)) + edge); // +SEGFAULT
    }
  }

  for (int vert1 = 0; vert1 < v; ++vert1) {
    for (int vert2 = 0; vert2 < v; ++vert2) {
      amat[vert1][vert2] = NONE;
    }
  }

  for (int edge = 0; edge < e; ++edge) {
    int vert1 = -1, vert2 = -1;
    for (int vert = 0; vert < v; ++vert) {
      if (imat[vert][edge] != NONE) {
        if (vert1 == -1) {
          vert1 = vert;
        } else if (vert2 == -1) {
          vert2 = vert;
        } else {
          printf("Malformed incidence matrix! Bailing\n");
          return 1;
        }
      }
    }
    amat[vert1][vert2] = amat[vert2][vert1] = imat[vert1][edge];
  }
  for (int vert1 = 0; vert1 < v; ++vert1) {
    for (int vert2 = 0; vert2 < v; ++vert2) {
      printf((vert2 == v - 1) ? "%lf" : "%lf ", amat[vert1][vert2]);
    }
    putchar('\n');
  }

  return 0;
}
