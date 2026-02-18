#include<stdio.h>

void swap(int* a, int* b) {
  int c = *a;
  *a = *b;
  *b = c;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  swap(&n, &m);
  swap(&n, &k);
  swap(&m, &k);
  printf("%d %d %d", n, m, k);

  return 0;
}

