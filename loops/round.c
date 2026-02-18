#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

const int U_BOUND = 1000000000; // = 10⁹

static bool is_05(int n) {
  int div;

  while (n != 0) {
    div = n % 10;
    if (div != 5 && div != 0) {
      return false;
    }
    n /= 10;
  }
  return true;
}


int main(int argc, char** argv) { 
  int n, c;
  c = 0;

  scanf("%d", &n);

  for (int i = 0; i < U_BOUND; i+=5) { // this is admittedly stupid
    if (is_05(i)) {
      c++;
    }
    if (c == n) {
      printf("%d", i);
      return 0;
    }
  }
}
