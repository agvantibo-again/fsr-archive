#include <stdio.h>

void swap(int* a, int* b) {
  int buf = *a;
  *a = *b;
  *b = buf;
}

int tri(int* n, int t, int s) {
  // number, target, state
  if (t == s) {
    return n[3];
  } else {
    swap(&n[0], &n[1]);
    swap(&n[1], &n[2]);
    swap(&n[2], &n[3]);
    n[3] = 3 * n[2] - 3 * n[1] + n[0];
    return tri(n, t, s+1);
  }
}

int main(int argc, char** argv) {
  int n;
  int bb[4] = {0, 0, 1, 3};
  scanf("%d", &n);
  if (0 <= n && n < 2) {
    printf("%d", bb[n + 1]);
  } else {
    printf("%d", tri(bb, n - 1, 1));
  }
  
  return 0;
}
