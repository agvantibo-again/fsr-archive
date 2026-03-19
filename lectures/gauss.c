#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>

static inline void swap(int* const a, int* const b) {
  int c = *a;
  *a = *b;
  *b = c;
}

void swap_rows(size_t const dim, int matrix[dim][dim], size_t const row_a, size_t const row_b) {
  for (size_t col = 0; col < dim; ++col) {
    swap(((int*)((int**)matrix + row_a)) + col, ((int*)((int**)matrix + row_b)) + col);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <matrix.txt>\n", argv[0]);
    return 1;
  }
  size_t m;
  FILE *mat_file = fopen(argv[1], "r");
  if (!mat_file) {
    fprintf(stderr, "Unable to read file!\n");
    return 1;
  }
  char *i_buf = readline("Matrix size (m) > ");
  if (!i_buf) {
    return 1;
  }
  m = (size_t)abs(atoi(i_buf));
  long matrix[m][m];
  int scan_ret;
  int piv_row, piv_col;
  piv_row = piv_col = 1;
  for (size_t row = 0; row < m; ++row) {
    for (size_t col = 0; col < m; ++col) {
      scan_ret = fscanf(mat_file, "%ld", &matrix[row][col]);
      if (scan_ret == EOF) {
        fprintf(stderr, "Insufficient ingress data\n!");
        return 1;
      }
    }
  }
  
  // printf("%lu\n", m);
  return 0;
}
