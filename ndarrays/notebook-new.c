#include<stdio.h>
#include<stdbool.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m;
  
  scanf("%d %d", &n, &m);
  getchar(); // eat \n
  bool page[n][m];
  int buffer;
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      buffer = getchar();
      page[r][c] = (buffer == '1');
    }
    getchar(); // eat \n
  }

  bool hlines[n];
  bool is_hline;

  // printf("hline map:");
  for (int r = 0; r < n; r++) {
    is_hline = true;
    for (int c = 0; c < m; c++) {
      // printf("%d ", scan[r][c]);
      is_hline = is_hline && (page[r][c]);
    }
    // putchar('\n');
    hlines[r] = is_hline; // false → 0, true → 1
    // printf(" %d", hlines[r]);
  }
  // putchar('\n');
  
  bool vlines[m];
  bool is_vline;

  // printf("vline map:");
  for (int c = 0; c < m; c++) {
    is_vline = true;
    for (int r = 0; r < n; r++) {
      is_vline = is_vline && (page[r][c]);
    }
    vlines[c] = is_vline;
    // printf(" %d", vlines[c]);
  }

  int v_count = 0;
  int v_distance = 0;
  int v_0 = -1;
  for (int c = 0; c < m && v_count < 2; ++c) {
    v_distance += v_count; // 0 until first line, then +1
    if (vlines[c]) {   
      v_count += 1;
      if (v_count == 1) {
        v_distance = 0;
        v_0 = c;
      }
    }
  } // find:
  // - distance between first 2 lines (v_distance)
  // - first line (v_0)  

  int h_count = 0;
  int h_distance = 0;
  int h_0 = -1;
  for (int r = 0; r < n && h_count < 2; ++r) {
    h_distance += h_count; // 0 until first line, then +1
    if (hlines[r]) {   
      h_count += 1;
      if (h_count == 1) {
        h_distance = 0;
        h_0 = r;
      }
    }
  }

  bool v_ok = true;
  if (v_count > 1) {
    v_count = 0;
    for (int c = v_0; c < m; ++c) {
      if ((c - v_0) % v_distance == 0) {
        v_ok = v_ok && vlines[c]; // every one of those should be a line
        ++v_count;
      } else {
        v_ok = v_ok && !vlines[c]; // and every one of those should not
      }
    }
  }

  bool h_ok = true;
  if (h_count > 1) {
    h_count = 0;
    for (int r = h_0; r < m; ++r) {
      if ((r - h_0) % h_distance == 0) {
        h_ok = h_ok && hlines[r]; // every one of those should be a line
        ++h_count;
      } else {
        h_ok = h_ok && !hlines[r]; // and every one of those should not
      }
    }
  }
  
  // if (
  //   (!h_ok && !v_ok)
  //     || (h_count == 0 && v_count == 0)
  //     || (v_distance != h_distance && h_count >= 2 && v_count >= 2)
  //     || (v_distance == 1 && v_count > 1)
  //     || (h_distance == 1 && h_count > 1)
  // ) {printf("?");} else
  // if (h_count >= 1 && v_count >= 1) {printf("Square");} else
  // if (h_count > 1) {printf("Line");} else
  // if (v_count > 1) {printf("Vertical line");}

  if (
    !h_ok ||
    !v_ok ||
    (h_count == 0 && v_count == 0) ||
    (n == 1 && m == 1) ||
    (h_count >= 2 && v_count >= 2 && h_distance != v_distance) ||
    (v_distance == 1 && v_count > 1) ||
    (h_distance == 1 && h_count > 1)
  ) {
      printf("?");
  } 
  else if (h_count >= 1 && v_count >= 1) {
      printf("Square");
  } 
  else if (h_count > 1) {
      printf("Line");
  } 
  else if (v_count > 1) {
      printf("Vertical line");
  }
  // remaining cases
  else {
      printf("?");
  }

  return 0;
}

