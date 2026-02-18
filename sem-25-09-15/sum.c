#include<stdio.h>

int main() {
  int n, t, s;
  s = 0;
  scanf("%d", &t);

  while (s <= t) {
    scanf("%d", &n);
    s += n;
  }
  printf("YES\n%d", s);
  return 0;
}
