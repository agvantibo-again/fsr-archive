#include <stdio.h>

struct Sum {
  int rub;
  int cop;
};

struct Sum change(struct Sum price, struct Sum paid) {
  struct Sum chg;
  chg.rub = paid.rub - price.rub;
  if (paid.cop < price.cop) {
    chg.rub -= 1;
    paid.cop += 100;
  }
  chg.cop = paid.cop - price.cop;
  return chg;
}

int main() {
  struct Sum price, paid, chg;
  scanf("%d%d%d%d", &price.rub, &price.cop, &paid.rub, &paid.cop);
  chg = change(price, paid);
  printf("%d %d", chg.rub, chg.cop);

  return 0;
}
