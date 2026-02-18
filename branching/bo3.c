#include <stdio.h>

static void swap(int * a, int * b) {
  int buffer = *a;
  *a = *b;
  *b = buffer;
}

int main() {
  int a, b, c;
  scanf("%d %d %d", &a, &b, &c);

  if (c > b) {
    swap(&b, &c);
  }
  if (b > a) {
    swap(&a, &b);
  }
  printf("%d\n", a);
  return 0;
}
