#include<stdio.h>
#include<stdbool.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m; // rows, cols
  scanf("%d %d", &n, &m);
  bool scan[n][m];
  char buffer;
  getchar(); // eat \n
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      scanf("%c", &buffer);
      scan[r][c] = (bool) (buffer - '0'); // evil character arithmetics
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
      is_hline = is_hline && (scan[r][c]);
    }
    // putchar('\n');
    hlines[r] = is_hline; // false → 0, true → 1
    // printf(" %d", hlines[r]);
  }
  // putchar('\n');
  
  bool vlines[n];
  bool is_vline;

  // printf("vline map:");
  for (int c = 0; c < m; c++) {
    is_vline = true;
    for (int r = 0; r < n; r++) {
      is_vline = is_vline && (scan[r][c]);
    }
    vlines[c] = is_vline;
    // printf(" %d", vlines[c]);
  }

  bool valid = true;
  for (int r = 0; r < n && valid; r++) {
    for (int c = 0; c < m && valid; c++) {
      valid = (vlines[c] || hlines[r] || !scan[r][c]);
    }
  }
  // putchar('\n');
  
  int n_hlines = 0;
  int distance = 0;
  int last_distance = distance;
  is_hline = true; // repurposed as a global flag for hlines being ok
  // bool valid = true; //redefined earlier
  for (int r = 0; r < n && is_hline && valid; r++) {
    if (hlines[r]) {
      n_hlines += 1;
      valid = (n_hlines <= 1 || distance != 1);
      is_hline = (
        (last_distance == distance || n_hlines <= 2)
        && valid
      );
      last_distance = distance;
      distance = 0;
    }
    distance += (bool)n_hlines; // +1 if there are any
  }
  
  int d_hlines = last_distance;
  is_hline = (
    is_hline
    && (n_hlines <= 1 || distance <= d_hlines)
  );  // check if trailing zeroes are conformant
  int n_vlines = 0;
  last_distance = distance;
  distance = 0;
  is_vline = true; // repurposed as a global flag for vlines being ok
  for (int c = 0; c < m && is_vline && valid; c++) {
    if (vlines[c]) {
      n_vlines += 1;
      valid = (
        (n_hlines <= 1 || n_vlines <= 1 || distance == d_hlines) // check if the squares are square
        && (n_vlines <= 1 || distance != 1) // check distance between lines
      );
      is_vline = ((last_distance == distance || n_vlines <= 2) && valid);
      last_distance = distance;
      distance = 0;
    }
    distance += (bool)n_vlines; // +1 if there are any
  }
  is_vline = (
    is_vline
    && (n_hlines <= 1 || distance <= d_hlines)
    && (n_vlines <= 1 || distance <= last_distance)
  ); // check if trailing zeroes are conformant

  if (!valid || n == 1 || m == 1) {
    printf("?");
  } else if (n_hlines && is_hline && n_vlines && is_vline) {
    printf("Square");
  } else if (n_hlines > 1 && is_hline) {
    printf("Line");
  } else if (n_vlines > 1 && is_vline) {
    printf("Vertical line");
  } else {
    printf("?");
  }
  putchar('\n');

  return 0;
}

