#include <stdio.h>

int main(void) {
  int n;

  scanf("%d", &n);

  const int a = (1 << n);
  for (int i = 0; i < a; ++i) {
    for (int j = n - 1; j >= 0; --j) {
      printf("%d ", (i >> j) & 0b1);
    }
    printf("\n");
  }
  return 0;
}
