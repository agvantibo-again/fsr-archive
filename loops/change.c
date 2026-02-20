#include <stdio.h>

int main() {
  int s, n, m, c;
  c = 0;

  scanf("%d %d", &s, &n);
  int p[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &p[i]);
  }
  scanf("%d", &m);
  int q[m];
  for (int i = 0; i < m; i++) {
    scanf("%d", &q[i]);
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) { // intj
      printf("%d %d", p[i], q[j]);
    }
  }
}
