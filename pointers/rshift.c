
#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n);

  int buf[n];
  for (int *i = buf; i < buf + n; ++i) {
    scanf("%d", i);
  }
  n--; // n is now max(i) for buf
  printf("%d ", *(((int *)buf) + n));
  for (int *i = buf; i < buf + n; ++i) {
    printf("%d ", *i);
  }
  putchar('\n');

  return 0;
}
