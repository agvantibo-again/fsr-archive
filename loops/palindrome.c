#include <stdio.h>


int main(int argc, char** argv) {
  int n, m;

  scanf("%d %d", &n, &m);
  n = (n < 1000) ? 1000 : n;
  m = (m > 9999) ? 9999 : m;

  for (; n <= m; n++) {
    if (n / 1000 == n % 10 && n % 1000 / 100 == n % 100 / 10) {
      printf("%d\n", n);
    }
  }

  return 0;
}
