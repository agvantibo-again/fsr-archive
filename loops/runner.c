#include<stdio.h>

int main() {
  int n, m, c;
  double nf;
  scanf("%d %d", &n, &m);
  c = 1;
  nf = n;

  while (nf < m) {
    nf = nf * 1.1;
    c += 1;
  }
  printf("%d", c);

  return 0;
}
