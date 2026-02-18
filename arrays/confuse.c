
#include<stdio.h>
#include<limits.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  long long int n, m, b, min, max;
  scanf("%lld %lld", &n, &m);
  min = LLONG_MAX;
  max = LLONG_MIN;

  for (int i = 0; i < n; i++) {
    scanf("%lld", &b);
    min = (b < min) ? b : min;
    max = (b > max) ? b : max;
  }
  printf("%lld\n", max - min);

  return 0;
}
