#include <stdio.h>
#include <stdbool.h>

#define BUF_MAX 10001
const int CAP_MAGIC = 'a' - 'A';

int toupper(int c) {
  if (96 < c && c < 123 ) {
    return c - (CAP_MAGIC); // ASCII to uppercase
  } else {
    return c;
  }
}

int main(int argc, char** argv) {
  int b, s, i;
  bool p_space;
  char input[BUF_MAX];
  scanf("%d", &s);
  getchar(); // flush \n
  b = '\t';  

  for (int i = 0; i < BUF_MAX; i++) {
    b = getchar();
    if (b == EOF || b == '\n') { // getchar() → -1 is an EOF
      input[i] = '\0';
    } else {
      input[i] = (char) b;
    }
  }
  
  i = 0;
  p_space = true;

if (s == 2) {
  while (input[i]) {
  	putchar(toupper(input[i]));
  	i++;
  }
} else {
  while (input[i]) {
    if (p_space) {
      putchar(toupper(input[i]));
    } else {
      putchar(input[i]);
    }
  	p_space = (input[i] == ' ');
  	i++;
  }
    
  }
  return 0;
}
