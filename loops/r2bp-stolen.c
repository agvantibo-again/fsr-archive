#include <stdio.h>

void swap(int *a, int *b) {}

int max2pow(int m) {
  int i = 0;
  while (m % 2 == 0) {
    m /= 2;
    ++i;
  }
  return i;
}

int gcd(int x, int y) {
  if (!x || !y)
    return x + y;
  if (x < y)
    swap(&x, &y);
  return gcd(x % y, y);
}

void bprint_rec(int n) {
  if (!n)
    return;
  bprint_rec(n >> 1);
  printf("%d", n & 1);
}

void solve() {
  int n, m, integerPart;

  int k = 0, g, mPow, t, bff;

  scanf("%d%d", &n, &m);
  integerPart = n / m;
  n %= m;
  g = gcd(n, m);
  n /= g;
  m /= g;

  mPow = max2pow(m);

  m >>= mPow;
  if (m == 1)
    t = 0;
  else {
    t = 1;
    bff = 2;
    while (bff % m != 1) {
      ++t;
      bff = ((bff << 1) % m);
    }
  }

  m <<= mPow;

  bprint_rec(integerPart);

  if (mPow || t) {
    printf(".");
    for (int i = 0; i < mPow; i++) {
      n <<= 1;
      printf("%d", n / m);
      n %= m;
    }
    if (t) {
      printf("(");
      for (int i = 0; i < t; i++) {
        n <<= 1;
        printf("%d", n / m);
        n %= m;
      }
      printf(")");
    }
  }
}
