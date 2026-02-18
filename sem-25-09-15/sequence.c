#include <stdio.h>
#include <stdbool.h>

int main() {
  int k;
  scanf("%d", &k);
  if (k <= 0) {
    printf("None");
    return 0;
  }

  bool p = false;
  double f;
  for (int i = 0; i < k; i++) {
    scanf("%lf", &f);
    if (!p) {
       printf("%lf ", f);
    }
    p = !p;
  }

  return 0;
}
