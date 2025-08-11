#include <stdio.h>
#include "structures.h"

int main() {
  ArrayList* cars = createArrayList(1);

  printf("Hello World");

  freeArrayList(cars);
  return 0;
}
