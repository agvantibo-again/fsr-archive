#include<stdio.h>

void swap(int* a, int* b) {
  int c = *a;
  *a = *b;
  *b = c;
}

int main(int argc, char** argv) {
  int buf, c;
  int queue[3] = {0, 0, 0};
  c = 0;
  buf = 1;

  while (buf != 0) {
    scanf("%d", &buf);
    swap(&queue[0], &queue[1]);
    swap(&queue[1], &queue[2]); // 0 ← 1, 1 ← 2, frees up 2 
    queue[2] = buf;
    
    if (
        queue[0] != 0 && buf != 0 // </3
        && queue[0] < queue[1]
        && queue[1] > queue[2]
      ) {
      c++;
    }
  }
  printf("%d", c);
  return 0;
}
