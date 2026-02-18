#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);

  for (int i = 0; i <= 1000; i++) {
    if (a * i * i * i + b * i * i + c * i + d == 0) {
      printf("%d\n", i);
    }
  }
  return 0;
}
