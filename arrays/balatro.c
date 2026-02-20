
#include <stdbool.h>
#include <stdio.h>

const int HAND = 5;

enum hand {
  NOTHING = 0,
  OAK_2, // pair
  TWOPAIR,
  OAK_3,
  STRAIGHT,
  FULLHOUSE,
  OAK_4,
  OAK_5
};

void swap(int *a, int *b) {
  int buf = *a;
  *a = *b;
  *b = buf;
}

void bsort(int l, int *a) {
  bool sorted = false;
  while (!sorted) {
    sorted = true;
    for (int i = 1; i < l; i++) {
      if (a[i] > a[i - 1]) {
        swap(&a[i], &a[i - 1]);
        sorted = false;
      }
    }
  }
}

void print_hand(enum hand kind) {
  switch (kind) {
  case OAK_5:
    printf("Impossible");
    break;
  case OAK_4:
    printf("Four of a Kind");
    break;
  case FULLHOUSE:
    printf("Full House");
    break;
  case OAK_3:
    printf("Three of a Kind");
    break;
  case OAK_2:
    printf("One Pair");
    break;
  case TWOPAIR:
    printf("Two Pairs");
    break;
  case STRAIGHT:
    printf("Straight");
    break;
  case NOTHING:
    printf("Nothing");
    break;
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  int h[HAND], unique[HAND], unicount[HAND];
  enum hand kind;
  for (int i = 0; i < HAND; i++) {
    scanf("%d", &h[i]);
    unique[i] = -1;
    unicount[i] = 0;
  }
  bsort(HAND, h);

  int i = 0;
  int j = 0;
  bool l_exit;
  while (i < HAND) {
    l_exit = false;
    j = 0;
    while (j < HAND && !l_exit) {
      if (h[i] == unique[j]) {
        unicount[j] += 1;
        l_exit = true;
      } else if (unique[j] == -1) {
        unicount[j] += 1;
        unique[j] = h[i];
        l_exit = true;
      }
      j++;
    }
    i++;
  } // kill me
  // this code could have been much _much_ clearer, but alas.
  // for (int i = 0; i < HAND; i++) {
  //   for (int j = 0; j < HAND; j++) {
  //     if (h[i] == unique[j]) {
  //       unicount[j] += 1;
  //       break;
  //     } else if (unique[j] == -1) {
  //       unicount[j] += 1;
  //       unique[j] = h[i];
  //       break;
  //     }
  //   }
  // }

  bsort(HAND, unicount);

  kind = STRAIGHT;
  i = 1;
  l_exit = false;
  while (i < HAND && !l_exit) {
    if (h[i - 1] != h[i] + 1) {
      kind = NOTHING;
      l_exit = true;
    }
    i++;
  }

  if (!kind) {
    switch (unicount[0]) {
    case 5:
      kind = OAK_5;
      break;
    case 4:
      kind = OAK_4;
      break;
    case 3:
      kind = (unicount[1] == 2) ? FULLHOUSE : OAK_3;
      break;
    case 2:
      kind = (unicount[1] == 2) ? TWOPAIR : OAK_2;
      break;
    default:
      break;
    }
  }

  print_hand(kind);

  return 0;
}
