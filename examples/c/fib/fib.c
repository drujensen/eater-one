#include <stdio.h>

static int fib(int n) {
  if (n <= 1) return 1;
  return fib(n - 1) + fib(n - 2);
}

int main(void) {
  printf("%d\n", fib(46));
  return 0;
}
