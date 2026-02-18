#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define endl putchar('\n')

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  int n, m; // rows, cols
  scanf("%d %d", &n, &m);
  bool balls[n][m];
  char buffer;
  getchar(); // eat \n
  for (int r = 0; r < n; ++r) {
    for (int c = 0; c < m; ++c) {
      scanf("%c", &buffer);
      balls[r][c] = (buffer == '#');
    }
    getchar(); // eat \n
  }

  int n_sculpt = n * 2 - 1;
  int m_sculpt = m * 2 - 1;
  char sculpt[n_sculpt][m_sculpt];

  memset(sculpt, '.', sizeof sculpt);

  for (int r = 0; r < n_sculpt; r += 2) {
    for (int c = 0; c < m_sculpt; c += 2) {
      if (balls[(int)r/2][(int)c/2]) {
        sculpt[r][c] = '#';
      }
    }
  }

  // set up vertical and horizontal connections
  for (int r = 0; r < n_sculpt; ++r) {
    for (int c = 1; c < m_sculpt-1; c+=2) {
      if (sculpt[r][c-1] == '#' && sculpt[r][c+1] == '#')
      {sculpt[r][c] = '-';} else {sculpt[r][c] = ' ';}
    }
  }
  for (int r = 1; r < n_sculpt-1; r+=2) {
    for (int c = 0; c < m_sculpt; ++c)
    if (sculpt[r+1][c] == '#' && sculpt[r-1][c] == '#')
    {sculpt[r][c] = '|';} else {sculpt[r][c] = ' ';}
  }

  // set up diagonal connections
  bool normal, backward;
  for (int r = 1; r < n_sculpt-1; r+=2) {
    for (int c = 1; c < m_sculpt-1; c+=2) {
      normal = (sculpt[r-1][c+1] == '#' && sculpt[r+1][c-1] == '#'); 
      backward = (sculpt[r+1][c+1] == '#' && sculpt[r-1][c-1] == '#');
      sculpt[r][c] = !normal && !backward ? ' ' :
                     normal && backward ? 'X' :
                     normal ? '/' : '\\'; // backward
    }
  }
  


  endl;
  for (int r = 0; r < n_sculpt; ++r) {
    for (int c = 0; c < m_sculpt; ++c) {
      printf("%c", sculpt[r][c]);
    }
    endl;
  }

  return 0;
}
