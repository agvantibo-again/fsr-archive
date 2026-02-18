#include<stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n;
  scanf("%d", &n);

  int buf[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &buf[i]);
  }
  n--; // n is now max(i) for buf
  printf("%d ", buf[n]);
  for (int i = 0; i < n; i++) {
    printf("%d ", buf[i]);
  }
  putchar('\n');

  return 0;
}

