#include<stdio.h>

#define yes printf( "YES");
#define no printf( "NO");

int main() {
  int y;
  scanf("%d", &y);

  if (y % 4 == 0) {
    if (y % 100 == 0) {
      if (y % 400 == 0) {
        yes
      } else {
        no
      }
    } else {
      yes
    }
  } else {
    no
  }
  return 0;
}
