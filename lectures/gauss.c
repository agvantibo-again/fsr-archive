#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>

typedef unsigned long ul;

static inline void swapld(long double *const a, long double *const b) {
  long double c = *a;
  *a = *b;
  *b = c;
}

void swap_rowsld(ul const dim, long double matrix[dim][dim], ul const row_a,
                 ul const row_b) {
  for (ul col = 0; col < dim; ++col) {
    swapld(((long double *)((long double **)matrix + row_a)) + col,
           ((long double *)((long double **)matrix + row_b)) + col);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <matrix.txt>\n", argv[0]);
    return 1;
  }
  ul m;
  FILE *mat_file = fopen(argv[1], "r");
  if (!mat_file) {
    fprintf(stderr, "Unable to read file!\n");
    return 1;
  }
  char *i_buf = readline("Matrix size (m) > ");
  if (!i_buf) {
    return 1;
  }
  m = (ul)abs(atoi(i_buf));
  long double matrix[m][m];
  int scan_ret;
  for (ul row = 0; row < m; ++row) {
    for (ul col = 0; col < m; ++col) {
      scan_ret = fscanf(mat_file, "%Lf", &matrix[row][col]);
      if (scan_ret == EOF) {
        fprintf(stderr, "Insufficient ingress data\n!");
        return 1;
      }
    }
  }

  long nonzero = 0;
  for (ul pivot = 0; pivot < m; ++pivot) {
    nonzero = -1; // index of first non-0 element 
    for (ul row = 0; row < m && nonzero == -1; ++row) {
      if (matrix[row][pivot] != 0) {
        nonzero = (long) row;
      }
    }
    if (nonzero >= 0) { // we've found something
      if (pivot < (ul)nonzero) { // and it's below the pivot, need to swap
        swap_rowsld(m, matrix, pivot, (ul)nonzero);
      }
      for (ul op_row = pivot + 1; op_row < m; ++op_row) {
        long double factor = matrix[op_row][pivot] / matrix[pivot][pivot];
        for (ul op_col = 0; op_col < m; ++op_col) {
          matrix[op_row][op_col] -= matrix[pivot][op_col] * factor;
        }
      }
    }
  }

  for (ul row = 0; row < m; ++row) {
    for (ul col = 0; col < m; ++col) {
      if (matrix[row][col] >= 0) {
        putchar(' ');
      }
      printf("%Lf\t", matrix[row][col]);
    }
    putchar('\n');
  }

  // printf("%lu\n", m);
  return 0;
}
