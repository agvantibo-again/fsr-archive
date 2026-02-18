#include<stdlib.h>
#include<stdio.h>

int main() {
  const int* i = malloc(sizeof(int));
  printf("%d", *i);
}
