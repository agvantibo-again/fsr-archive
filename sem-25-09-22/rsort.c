#include <stdbool.h>
#include <stdio.h>

void swap_lf(double *a, double *b) {
  double buf = *a;
  *a = *b;
  *b = buf;
}

void bsort_lf(int l, double *a) {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i = 1; i < l; i++) {
      if (a[i] > a[i - 1]) {
        swap_lf(&a[i], &a[i - 1]);
        sorted = false;
      }
    }
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n);
  double a[n];
  for (int i = 0; i < n; i++) {
    scanf("%lf", &a[i]);
  }
  bsort_lf(n, a);

  for (int i = 0; i < n; i++) {
    printf("%lf", a[i]);
    if (i != n - 1) {
      putchar(',');
      putchar(' ');
    }
  }

  return 0;
}
