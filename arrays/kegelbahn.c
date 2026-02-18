
#include<stdio.h>
#include<stdbool.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, k, l, r;
  scanf("%d %d", &n, &k);
  bool p[n];
  for (int i = 0; i < n; i++) {
    p[i] = true;
  }
  for (int i = 0; i < k; i++) {
    scanf("%d %d", &l, &r);
    l--; r--;
    for (int j = l; j <= r; j++) {
      p[j] = false;
    }
  }
  
  for (int i = 0; i < n; i++) {
    putchar((p[i]) ? 'I' : '.');
  }
  putchar('\n');

  return 0;
}
