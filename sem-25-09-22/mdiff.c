#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int il(int i) {
  if (i == 0) { // !i works too but would be much more opaque
    return 1;
  } else {
    return (int) floor(log10(abs(i))); 
  }
}

int main(int argc, char** argv) {
  int n, m, b, sep;
  scanf("%d %d", &n, &m);
  int mta[n][m];
  sep = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &mta[i][j]);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &b);
      mta[i][j] -= b;

      b = il(mta[i][j]) + 1;
      sep = (b > sep) ? b : sep;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      b = il(mta[i][j]) + 1;
      if (j == 0) { b += 1; }
      for (int k = 0; k <= sep - b; k++) {putchar(' ');}
      printf((mta[i][j] >= 0) ? "+" : "");
      printf("%d", mta[i][j]);
    } putchar('\n');
  }
}
