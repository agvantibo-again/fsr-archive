#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int n;
  bool sb = false;
  scanf("%d", &n);

  if (n == 1) {
    putchar('0');
    return 0;
  }
  n--;

  for (int i = sizeof n * 8 - 1; i >= 0; i--) {
    if (n & (1 << i)) { // mask all bits except i-th one
      sb = true;
      putchar('5');
    } else if (sb) {
      putchar('0');
    }
  }
  return 0;
}
