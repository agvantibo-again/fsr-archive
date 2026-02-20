
#include <stdbool.h>
#include <stdio.h>

void read_photo(int n, int m, char arr[n][m]) {
  int buf;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      buf = getchar();
      // fprintf(stderr, "%c(%d)", buf, buf);
      if (buf == '\n' || buf == '\r') {
        fprintf(stderr, "!");
      }
      arr[i][j] = (char)buf;
    }
    getchar();
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n, m, ans;
  scanf("%d %d", &n, &m);
  getchar(); // flush \n
  char img1[n][m], img2[n][m];

  read_photo(n, m, img1);
  getchar();
  read_photo(n, m, img2);

  ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      // printf("%c %c ", img1[i][j], img2[i][j]);
      if (img1[i][j] == img2[i][j]) {
        ans += 1;
      }
      // putchar('\n');
    }
  }
  printf("%d\n", ans);

  return 0;
}
