#include<stdio.h>
#include<stdbool.h>

// madness. TitleCase is for structs
bool IsPointInSquare(double x, double y) {
  return (
    x >= -1 &&
    y >= -1 &&
    x <= 1 &&
    y <= 1
  );
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  double x, y;
  scanf("%lf %lf", &x, &y);
  printf(IsPointInSquare(x, y) ? "YES" : "NO");

  return 0;
}
