
#include<stdio.h>

int gcd(int const n, int const m) {
  if (m == 0) {
    return n;
  } else {
    return gcd(m, n % m);
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  printf("%d", gcd(n, m));
  return 0;
}
