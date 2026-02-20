#include <stdio.h>

enum TOWERS { T_SRC = 1, T_DEST = 2, T_AUX = 3 };

static inline void tower_move(int const disk, int const src, int const dest) {
  printf("Disk %d move from %d to %d\n", disk, src, dest);
}

void hanoi(int const n, int const src, int const dest, int const aux) {
  if (n == 1) {
    tower_move(1, src, dest);
  } else {
    hanoi(n - 1, src, aux, dest);
    tower_move(n, src, dest);
    hanoi(n - 1, aux, dest, src);
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n);
  hanoi(n, T_SRC, T_DEST, T_AUX);

  return 0;
}
