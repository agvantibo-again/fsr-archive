'''
#include <stdio.h>
#include <stdbool.h>

int calc(int s, int e) {
  if (s == e) {
    return 1;
  } else if (s > e) {
    return 0;
  } else {
    return calc(s + 3, e) + calc(s + 5, e);
  }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
  bool ans[200];

  for (int i = 0; i < 200; ++i) {
    printf("%d\n", i + 1);
    fflush( stdout );
    ans[i] = (bool) calc(1, i + 1);
  }

  printf(" = { ");
  for (int i = 0; i < 200 - 1; ++i) {
    printf("%d, ", ans[i]);
  }
  printf(" };\n");

  return 0;
}
'''
import functools

@functools.cache
def calc(s, e):
    if s == e:
        return 1
    elif s > e:
        return 0
    else:
        return calc(s + 3, e) or calc(s + 5, e)

# print("ans = {")
for i in range(200):
    print(f"{i+1}: {bool(calc(1, i+1))}")
# print("};")

