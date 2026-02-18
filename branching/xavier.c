#include <stdio.h>
#include <assert.h>

const int xavier = 1605;

int virm(int b, int d) {
  int ans = (d - b) / 10 + 1;
  if (b < xavier) {
    ans -= (xavier - b) / 10 + 1;
  }
  if (b % 10 >= 5) {
    ans -= 1;
  }
  if (d % 10 < 5) {
    ans -= 1;
  }
  // if (ans < 0) {
  //   return 0;
  // } else {
    return ans;
  // }
}

int main() {
  assert((virm(1610, 1640) == 3) && "test 1 failed (1610, 1640)"); // условие 1
  assert((virm(1615, 1645) == 3) && "test 2 failed (1615, 1644)"); // условие 2
  // assert((virm(1500, 1590) == 0) && "test 2 failed (1500, 1590)"); // умер раньше
  // assert((virm(1600, 1590) == 0) && "test 2 failed (1500, 1590)"); //
  int b, d;
  scanf("%d %d", &b, &d);
  printf("%d", virm(b, d));
  return 0;
}
