#include <alloca.h>
#include <stdio.h>

/* This doesn't require an array at all, just a loop */

int main(int argc, char **argv) {
  int n, max, buf;
  buf = max = 0x80000000; // is the minimum for a 32 bit signed integer
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &buf);
    max = (buf > max) ? buf : max;
  }
  printf("%d", max);

  return 0;
}
