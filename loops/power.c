
#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<math.h>

#define A_MAX_LEN 6144
#define OVERFLOW 1000000L
#define L_OVERFLOW 6L
// log10(OVERFLOW)

void a_print(int l, long int array[l]) {
  int first_significant = l + 1;
  for (int i = l; i >= 0 && first_significant == l + 1; --i) {
    if (array[i]) {
      first_significant = i;
      printf("%ld", array[i]);
    }
  }

  int z_pad;
  if (first_significant == l + 1) {
      putchar('0');
  } else {
    for (int i = first_significant - 1; i >= 0; --i) {
      z_pad = L_OVERFLOW - ((int) floor(log10l(array[i])) + 1);
      for (int j = 0; j < z_pad; ++j) {putchar('0');}
      printf("%ld", array[i]);
    }
  }
  
  putchar('\n');
}


void a_mul(int l, long int array[l], char m) {
  long int carry = 0;
  for (int i = 0; i < l; ++i) {
    long int product = array[i] * m + carry;
    array[i] = product % OVERFLOW;
    carry = product / OVERFLOW;
  }
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n;
  scanf("%d", &n);
  long int ans[A_MAX_LEN] = {1, 0};
  for (int i = 0; i < n; ++i) {
    a_mul(A_MAX_LEN, ans, 2);
  }
  
  a_print(A_MAX_LEN, ans);

  return 0;
}
