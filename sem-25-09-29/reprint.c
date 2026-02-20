#include <stdio.h>

void printer_hp(int i, int n, int *from) // very bad printer
{
  if (i < n) {
    printf((from[i] >= 0) ? "+" : "");
    printf("%d", from[i]);
    printf((i != n - 1) ? "; " : " ");
    printer_hp(i + 1, n, from);
  }
}

int main(int argc, char **argv) {
  int n;
  scanf("%d", &n);
  int input[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &input[i]);
  }
  printer_hp(0, n, input);
  putchar('\n');

  return 0;
}
