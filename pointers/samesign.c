
#include<stdio.h>
#include<stdbool.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n; int b[2] = {0, 0};
  bool pair = false;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    #define b_0 b
    #define b_1 (b + 1)
    *b_0 = *b_1;
    scanf("%d", b_1);

    if (i > 0 && (*b_0 >= 0) == (*b_1 >= 0)) { // agvantibo can't read
      pair = true;
    }
  }
  if (pair) {
    printf("YES");
  } else {
    printf("NO");
  }
  
  return 0;
}
