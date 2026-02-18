
#include<stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, buf, borderlands = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &buf);
      if (i == 0 || j == 0 || i == n-1 || j == n-1) {
        borderlands += buf;
      }
    }
  }
  printf("%d", borderlands);

  return 0;
}
