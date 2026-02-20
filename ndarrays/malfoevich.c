#include <stdbool.h>
#include <stdio.h>

struct pair {
  int r, c;
};

struct pair index_of_2da(int const n, int const m, char const scan[n][m],
                         char const f) {
  int r_0 = 0;
  int c_0 = 0;
  bool found = false;
  for (r_0 = 0; r_0 < n && !found; ++r_0) {
    for (c_0 = 0; c_0 < m && !found; ++c_0) {
      if (scan[r_0][c_0] == f) {
        found = true;
      }
    }
  } // find first black square
  --r_0;
  --c_0; // since we haven't broken out, both got incremented by 1

  // printf("r_0: %d, c_0: %d\n", r_0, c_0);
  struct pair ans = {.r = found ? r_0 : -1, .c = found ? c_0 : -1};
  return ans;
}

bool fill_next_rect(int const n, int const m, char scan[n][m], char const f) {
  struct pair c_0 = index_of_2da(n, m, scan, '#');
  if (c_0.r == -1) {
    return false; // early return if rect not found
  }
  int row_end = 0;

  int r = c_0.r;
  int c = c_0.c;
  for (r = c_0.r; r < n && scan[r][c] == '#';
       ++r) { // short-circuits because of the former
    for (c = c_0.c; c < m && (!row_end || c < row_end); ++c) {
      if (scan[r][c] != '#') {
        row_end = c;
      } else {
        scan[r][c] = f;
      }
    }
    c = c_0.c;
  }
  return true;
}

int count_in_2da(int const n, int const m, char scan[n][m], char const f) {
  int cnt = 0;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      if (scan[r][c] == f) {
        cnt += 1;
      }
    }
  }

  return cnt;
}

static bool generate_b(int const n, int const m, char scan[n][m]) {
  struct pair ca_0 = index_of_2da(n, m, scan, 'a');
  if (count_in_2da(n, m, scan, 'a') <=
      1) { // return early if we cant produce rect b
    return false;
  }
  if (ca_0.c + 1 == m ||
      scan[ca_0.r][ca_0.c] != 'a') { // edge case: a is 1 wide
    scan[ca_0.r][ca_0.c] =
        'b'; // b is 1x1 at the beginning of a, a is an 1xk strip
    return true;
  }
  for (int r = ca_0.r; r < n; ++r) {
    if (scan[r][ca_0.c] == 'a') {
      scan[r][ca_0.c] = 'b';
    }
  }
  return true;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n, m;
  scanf("%d %d", &n, &m);
  getchar(); // eat \n

  char scan[n][m];
  // int buffer;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      scan[r][c] = (char)getchar();
    }
    getchar(); // eat \n
  }
  if (fill_next_rect(n, m, scan, 'a') &&
      (fill_next_rect(n, m, scan, 'b') || generate_b(n, m, scan)) &&
      !count_in_2da(n, m, scan, '#')) {
    printf("YES\n");
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < m; ++c) {
        putchar(scan[r][c]);
      }
      putchar('\n');
    }
  } else {
    printf("NO\n");
  }

  return 0;
}
