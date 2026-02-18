#include <stdio.h>

const int xavier = 1605;

int main() {
  int b, d, c;

  scanf("%d %d", &b, &d);
  c = 0;
  
  for (int i = b + 1; i <= d; i++) { // фиаско
    if (i >= xavier && i % 10 == 5) {
      c += 1;
    }
  }

  printf("%d", c);
}
