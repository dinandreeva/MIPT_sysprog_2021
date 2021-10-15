#include <stdio.h>

int main() {
  float a = 0.0 * (-2);
  float b = a;
  float c = a;
  if (b == 0) {
      b = 0;
  }
  if (c == 0) {
      c = c + 0.0;
  }
  printf("raw %f\n", a);
  printf("fix #1 %f\n", b);
  printf("fix #2 %f\n", c);
  return 0;
}
