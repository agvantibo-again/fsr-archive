#include <stdbool.h>
#include <stdio.h>

bool is_div(int n, int m) {
  if (m == 0) {
    return false;
  } else if (n % m == 0) {
    return true;
  } else {
    return false;
  }
}

int main() {
  int i, j;
  scanf("%d%d", &i, &j);

  if (is_div(i, j)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }
  return 0;
}
