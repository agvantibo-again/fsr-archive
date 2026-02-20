#include <stdbool.h>
#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n);
  printf((n == 2 || n == 3 || n == 5 || n == 8) ? "NO" : "YES");

  return 0;
}
