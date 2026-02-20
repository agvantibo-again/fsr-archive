#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define FLOAT_TOLERANCE 1e-4L

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n, m;
  int ans[256];
  long double rem[256] = {0.0};
  double frac, f, integ;
  bool per = false; // have to initialize false for while loop
  scanf("%d %d", &n, &m);
  f = (double)n / m;
  memset(ans, -1, sizeof ans);
  // As of C23, VLAs can now be initialised with an empty initialiser { },
  // which, acting as with other compound types will initialise each element
  // and sub-element recursively to zero of the appropriate type.
  //
  // BUT NOT ON THE informatics.msk.ru compiler!!!

  for (int i = 0; !per && f != 0 && i < (int)(sizeof(ans) / sizeof(int)); i++) {
    f *= 2;
    per = false;
    frac = modf(f, &integ);
    // printf("integer %f frac %f\n", integ, frac);
    for (int i = 0; i < (int)(sizeof rem / sizeof(long double)); i++) {
      if (rem[i] == 0.0L) { // end of allocated remainders
        rem[i] = frac;
        break;
      } else if (fabsl(rem[i] - frac) < FLOAT_TOLERANCE) {
        per = true;
        break;
      }
    }
    ans[i] = (integ < 1) ? 0 : 1;
    f = frac;
  }
  // AAAAAAAAA (aaaaaaaaaa)

  for (int i = sizeof ans / sizeof(int) - 1;
       ((i >= 0 && ans[i] == -1) || ans[i] == 0); i--) {
    ans[i] = -1;
  }

  putchar('0');
  putchar('.');
  if (per) {
    putchar('(');
  }
  for (int i = 0; i < (int)(sizeof(ans) / sizeof(int)) && ans[i] != -1; i++) {
    printf("%d", ans[i]);
  }
  if (per) {
    putchar(')');
  }
  // putchar('\n');

  return 0;
}
