#include <stdio.h>

int main() {
  int a, b, c;

  scanf("%d %d %d", &a, &b, &c);
  if (c < a) {
    printf("NO GRAD");
  } else if (c < b) {
    printf("GRAD");
  }
  return 0;
}
