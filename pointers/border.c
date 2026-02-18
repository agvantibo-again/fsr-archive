
#include<stdio.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, buf, borders = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // indexing into a 2d array:
      // *(((type*)array + i_row * l_row) + j_col) ≡ array[i_row][j_col]
      scanf("%d", &buf);
      if (i == 0 || j == 0 || i == n-1 || j == n-1) {
        borders += buf;
      }
    }
  }
  printf("%d", borders);

  return 0;
}
