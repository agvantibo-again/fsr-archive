#include <stdio.h>

struct page {
  char lang;
  int page;
};

const struct page empty_page = {
    .lang = '-',
    .page = -1,
};

void print_page_or_die(struct page p) {
  if (p.lang == '-') {
    printf("- -");
  } else {
    printf("%c %d", p.lang, p.page);
  }
  printf("\n");
} // мне кажется, как-то так себя чувствовал Виктор Франкенштейн

int main() {
  int n, m, p, s_book;
  // struct page book[2048];

  scanf("%d%d%d", &n, &m, &p);
  s_book = n + m;
  s_book += s_book % 2;
  p--;

  struct page book[s_book - 1];

  for (int i = 0; i < s_book; i++) {
    if ((i + 1) <= n) {
      book[i].page = i + 1;
      book[i].lang = 'P';
    } else if (i >= (s_book - m)) {
      book[i].page = s_book - i - 1;
      book[i].lang = 'C';
    } else {
      book[i] = empty_page;
    }
  }

  print_page_or_die((p * 2 < s_book) ? book[p * 2] : empty_page);
  print_page_or_die((p * 2 < s_book) ? book[p * 2 + 1] : empty_page);

  return 0;
}
