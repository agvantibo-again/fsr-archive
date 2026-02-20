#include <stdio.h>
#include <stdlib.h>

int main() {
  const int *i = malloc(sizeof(int));
  printf("%d", *i);
}
