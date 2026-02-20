#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> // memcpy

#define lseq_max 31

typedef struct n_int_array {
  size_t len;
  bool ok;
  int *a;
} IntArr;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int n;
  scanf("%d", &n);
  getchar(); // eat \n

  int buffer[lseq_max], b;
  IntArr sequences[n];
  for (int i = 0; i < n; ++i) {
#define seq sequences[i]
    // grab a short handle for the sequence we're reading
    seq.len = 0;
    seq.ok = false;
    scanf("%d", &b);
    while (seq.len < lseq_max && b != 0) {
      buffer[seq.len] = b;
      scanf("%d", &b);
      ++seq.len;
    }
    // printf("Segment done");
    seq.a = malloc(sizeof(int) * seq.len);
    memcpy(seq.a, buffer, sizeof(int) * seq.len);
    seq.ok = (bool)(seq.a);
  }

  for (int i = 0; i < lseq_max; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i < (int)sequences[j].len) {
        printf("%d ", sequences[j].a[i]);
      }
    }
  }

  return 0;
}
