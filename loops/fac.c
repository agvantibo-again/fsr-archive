#include<stdio.h>

int main(int argc, char** argv) {
  unsigned int n, sum, fac;
  sum = 1; fac = 1;
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    fac *= i;
    sum += fac;
  }

  printf("%d", sum);
  
  return 0;
}
