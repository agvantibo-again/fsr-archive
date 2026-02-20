#include <stdbool.h>
#include <stdio.h>

int toupper(int c) {
  if (96 < c && c < 123) {
    return c ^ 32; // ASCII to uppercase
  } else {
    return c;
  }
}

int main(int argc, char **argv) {
  int s, i;
  bool p_space;
  char input[1024];
  scanf("%d", &s);
  fgets(input, sizeof input, stdin);
  fgets(input, sizeof input, stdin);

  i = 0;
  p_space = true;
  while (input[i]) {
    if ((s == 1 && p_space) || s == 2) {
      putchar(toupper(input[i]));
    } else {
      putchar(input[i]);
    }
    p_space = (input[i] == ' ');
    i++;
  }
  return 0;
}
