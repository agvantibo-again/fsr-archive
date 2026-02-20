#include <math.h>
#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  unsigned int n, l, mask;
  scanf("%u", &n);
  l = (unsigned int)floor(log2(n)) + 1U;
  mask = 0;
  for (unsigned int i = 0; i < l; i++) {
    mask += 1U << i;
    // printf("i: %b; mask: %b\n", 1U << i, mask);
  }

  // printf("n %b; bit length %u; mask %b", n, l, mask);
  printf("%u", (~n) & mask); // WOOOOOW *bitcrushed applause*

  return 0;
}
