#include<stdio.h>

int main() {
  double r, k, u;
  int T;
  scanf("%lf %lf %lf %d", &r, &k, &u, &T);

  for (int t = 0; t < T; t++) {
    u = r * u * (1-u/k);
  }
  printf("%lf", u);  

  return 0;
}
