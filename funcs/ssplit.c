#include <stdio.h>

void psum(int const n, int const m, int const diff) {
  for (int i = 0; i < diff; ++i) {
    printf("1 ");
  }
  if (n != 0) {
    if (m != 0) {
      printf("%d %d\n", n, m);
    } else {
      printf("%d\n", n);
      psum(n / 2, n / 2 + (n % 2), diff);
    }
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n); // write to first element
  psum(n, 0, 0);

  return 0;
}
