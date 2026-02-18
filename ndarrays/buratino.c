
#include<stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m, c, buf;
  scanf("%d %d", &n, &m);
  c = 0;
  getchar(); // flush \n
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      buf = getchar();
      c += (buf == '*') ? 1 : 0;
    }
    getchar();
  }
  buf = n * m; // total tiles
  if (buf - c < c) {
    putchar('1');
  } else if (buf - c > c) {
    putchar('2');
  } else {
    putchar('0');
  }
  putchar('\n');

  return 0;
}
