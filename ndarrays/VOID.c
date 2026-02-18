#include<stdio.h>

int wrap(int i, int n) {
  return (i + n) % n;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, x, y; // x→ and y↑
  scanf("%d", &n);
  if (!(n % 2)) { // n % 2 == 0
    return 1;
  }
  int a[n][n];
  for (int i = 0; i < n*n; i++) {
    ((int*)a)[i] = 0;
  }
  x = (int) ((n - 1) / 2);
  y = n-1;
  for (int i = 1; i <= n*n; i++) {
    x = wrap(x, n); y = wrap(y, n);
    if (a[(n-1)-y][x]) {
      y -= 2;
      --x;
      x = wrap(x, n); y = wrap(y, n);
    }
    a[(n-1)-y][(x) % n] = i;
    // printf("(%d, %d) = %d\n", x, (n-1)-y, i);
    ++y;
    ++x;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", a[i][j]);
    }
    putchar('\n');
  }

  return 0;
}

