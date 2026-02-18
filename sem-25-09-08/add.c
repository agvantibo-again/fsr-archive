#include <stdio.h>
#include <math.h>

int main() {
  int m, n;
  int margin; 

  scanf("%d%d", &m, &n);
  margin = floor(log10(n + n)) + 1;

  for (int j = m; j <= n; j++) {
    for (int i = m; i <= n; i++) {
      printf("%*d ", margin, i + j);
    }
    printf("\n");
  }
  
  return 0;
}
