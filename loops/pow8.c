#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define A_MAX_LEN 32000
#define BASE 10000000000

typedef struct u_arbitrary {
  unsigned int l_significand;
  int* significand;
} u_arbitrary;

void u_arbitrary_print(u_arbitrary n) {
  bool sig_digit = false;

  for (unsigned int i = 0; i < n.l_significand; i++) {
    if (sig_digit) {
      putchar(n.significand[i] + 48); // maps i0 — i9 → '0' — '9'
    } else {
      if (n.significand[i]) {
        sig_digit = true;
        i--;
      }
    }
  }
  if (!sig_digit) {
    putchar('0');
  }
  putchar('\n');
}

static void u_arbitrary_mul(u_arbitrary* n, char m) {
  // this is designed to work only for m < 10
  // if this were a stdlib function this is where I'd tell you to never use it

  char carry = 0;
  int mantisse[n->l_significand];

  // As of C23, VLAs can now be initialised with an empty initialiser { },
  // which as with other compound types will initialise each element
  // and sub-element recursively to zero of the appropriate type.
  //
  // not on informatics.msk.ru apparently.
  // grandiose.
  memset(mantisse, -1, sizeof(mantisse));

  u_arbitrary res = {
    .l_significand = n->l_significand,
    .significand = mantisse
  }; // idc if this shadows anything
  for (int i = (int) n->l_significand - 1; i >= 0; i--) {
    // I should really check for bounds
    int product = n->significand[i] * m + carry;
    res.significand[i] = product % BASE;
    carry = (char) product / BASE;
  }
  memcpy(n->significand, res.significand, sizeof(char[n->l_significand]));
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n;
  scanf("%d", &n);
  int mantisse[A_MAX_LEN];
  memset(mantisse, 0, sizeof(mantisse));
  u_arbitrary res = {
    .l_significand = A_MAX_LEN,
    .significand = mantisse
  };
  res.significand[res.l_significand-1] = 1; // → i1

  for (int i = 0; i < n; i++) {
    u_arbitrary_mul(&res, 2);
  }

  u_arbitrary_print(res);

  return 0;
}
