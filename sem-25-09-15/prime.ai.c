
#include <stdbool.h>
#include <stdio.h>

bool isPrime(int n) {
  // Обработка граничных случаев
  if (n <= 1)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  // Проверка делителей вида 6k ± 1
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

void checkPrimesInRange(int start, int end) {
  printf("Простые числа в диапазоне %d-%d:\n", start, end);
  for (int i = start; i <= end; i++) {
    if (isPrime(i)) {
      printf("%d ", i);
    }
  }
  printf("\n");
}

int main() {
  int num;
  printf("Проверка числа на простоту:\n");
  printf("Введите число: ");
  scanf("%d", &num);

  if (isPrime(num)) {
    printf("%d - простое число\n", num);
  } else {
    printf("%d - составное число\n", num);
  }

  // Дополнительно: поиск простых чисел в диапазоне
  checkPrimesInRange(1, 100);

  return 0;
}
