
#include <stdbool.h>
#include <stdio.h>

int sum_a_b(int const l, bool const a[l]) { // sum of boolean array
  int sum = 0;

  for (int i = 0; i < l; ++i) {
    sum += a[i];
  }

  return sum;
}

int sum_2dac_b( // sum of boolean 2darr column
    int const n, [[maybe_unused]] int const m, bool const a[n][m],
    int const col) {
  int sum = 0;

  for (int r = 0; r < n; ++r) {
    sum += a[r][col];
  }

  return sum;
}

int dist1_b(int const l, bool const a[l]) {
  // find distance between first two true's
  int dist = 0;
  int count = 0;
  for (int i = 0; i < l && count < 2; i++) {
    ++dist;
    if (a[i]) {
      ++count;
      if (count == 1) {
        dist = 0;
      }
    }
  }
  return count >= 2 ? dist : -1;
}

int dist1_2dac_b(int const n, [[maybe_unused]] int const m, bool const _a[n][m],
                 int const col) {
  bool a[n];
  for (int r = 0; r < n; ++r) {
    a[r] = _a[r][col];
  }
  return dist1_b(n, a);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  getchar();

  if (n <= 1 || m <= 1) { // edge case: algorithm goes OOB
    printf("?\n");
    return 0;
  }

  bool book[n][m];
  int buf;

  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m;) {
      buf = getchar();
      if (buf == '1' || buf == '0') {
        book[r][c] = (bool)(buf - '0');
        ++c;
      }
    }
  }
  // putchar('\n');

  int const sr[2] = {sum_a_b(m, book[0]), sum_a_b(m, book[1])};
  int const sc[2] = {sum_2dac_b(n, m, book, 0), sum_2dac_b(n, m, book, 1)};
  int const hlines_on = sc[0] > sc[1];
  int const vlines_on = sr[0] > sr[1];

  if (sc[hlines_on] && sr[vlines_on]) {
    printf("Square");
  } else if (sc[hlines_on] == 1 || sr[vlines_on] == 1) {
    printf("?");
  } else if (sc[hlines_on]) {
    printf(dist1_b(m, book[vlines_on]) < n ? "Line" : "?");
  } else if (sr[vlines_on]) { // (sr[vlines_on])
    printf(dist1_2dac_b(n, m, book, hlines_on) < m ? "Vertical line" : "?");
  } else {
    printf("?");
  }
  putchar('\n');
  // for (int r = 0; r < n; ++r) {
  //   for (int c = 0; c < m; ++c) {
  //     printf("%d", book[r][c]);
  //   }
  //   putchar('\n');
  // }
  return 0;
}
