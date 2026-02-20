
#include <stdio.h>

int main() {
  int n, c;
  n = 1;
  c = 0;

  while (n >= 0) {
    scanf("%d", &n);
    c++;
  }

  printf("Finally, it took you only %d attempts!", c);
  return 0;
}
