#include <stdbool.h>
#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n, h;
  bool printed;
  scanf("%d", &n);
  int row[n];

  for (int i = 0; i < n; i++) {
    scanf("%d", &row[i]);
  }

  scanf("%d", &h);

  printed = false;
  for (int i = n - 1; i >= 0; i--) {
    if (row[i] >= h) {
      printf("%d", i + 2);
      printed = true;
      // +1 because i_0 start at 0, +1 because we want the next place
      break;
    }
  }
  if (!printed) {
    putchar('1'); // if we haven't found a place yet, we're №1
  }

  return 0;
}
