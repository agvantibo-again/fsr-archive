#include <stdio.h>


int main(int argc, char** argv) {
  unsigned long long int n, m;
  scanf("%llu", &n);
  m = 1ULL << n;
  printf("%llu", m);

  return 0;
}
