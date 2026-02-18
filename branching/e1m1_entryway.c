#include<stdio.h>

int main() {
  int x, y;  // x, y — включительно и включительно
  scanf("%d %d", &x, &y);

  if ((x - 1) % (y - x + 1) != 0) {
    printf("NO");
  } else {
    printf("YES");
  }
  
  return 0;
}
