#include <stdio.h>

void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

int main(int argc, char **argv) {
  int buf, max1, max2;
  buf = 1;
  max1 = max2 = 0;

  while (buf != 0) {
    scanf("%d", &buf);

    // printf("%d %d %d\n", max1, max2, buf);
    if (buf > max1) {
      swap(&max1, &max2);
      max1 = buf;
    } else if (buf > max2) {
      max2 = buf;
    }
  }

  printf("%d", max2);
  return 0;
}
