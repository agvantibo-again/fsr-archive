#include <stdbool.h>
#include <stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  int b[2] = {0, 0};
  bool pair = false;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    b[0] = b[1];
    scanf("%d", &b[1]);

    if (i > 0 && (b[0] >= 0) == (b[1] >= 0)) { // agvantibo can't read
      pair = true;
    }
  }
  if (pair) {
    printf("YES");
  } else {
    printf("NO");
  }

  return 0;
}
