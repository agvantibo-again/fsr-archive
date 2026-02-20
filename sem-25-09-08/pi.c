#include <stdio.h>
#include <string.h>

const char pi[8] = "3.14159";

int main() {
  char uinput[8];

  fgets(uinput, sizeof(uinput) / sizeof(char), stdin);

  // printf("%s\n", uinput);
  // printf("%s\n", pi);
  if (!strncmp(uinput, pi, 8)) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }

  return 0;
}
