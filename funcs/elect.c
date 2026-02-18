#include<stdio.h>
#include<stdbool.h>

bool elect(bool n, bool m, bool k) {
  return (n * m + n * k + m * k);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);

  printf("%d", elect(n, m, k));
  return 0;
}

