#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int s, i;
  char inp[1024];
  scanf("%d", &s);
  fgets(inp, sizeof inp, stdin); // eats \n from the scanf
  fgets(inp, sizeof inp, stdin);

  char *tok = strtok(inp, " ");
  while (tok) {
    i = 1;
    putchar(toupper(tok[0]));

    while (tok[i]) {
      if (s > 1) {
        putchar(toupper(tok[i]));
      } else {
        putchar(tok[i]);
      }
      i++;
    }
    putchar(' ');
    tok = strtok(NULL, " ");
  }
  return 0;
}
