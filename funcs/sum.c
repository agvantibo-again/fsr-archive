#include<stdio.h>

int r_sum(int i) {
  int buf;
  scanf("%d", &buf);
  return (buf == 0) ? i : r_sum(i + buf);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  printf("%d\n", r_sum(0));

  return 0;
}

