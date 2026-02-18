#include<stdio.h>

int main(int argc, char** argv) {
  int n;
  scanf("%d", &n);
  int a[n];

  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; i++) {
    printf((a[i] > 0) ? "+" : "");
    printf("%d", a[i]);
    printf((i != n - 1) ? "; " : " ");
  }
}
