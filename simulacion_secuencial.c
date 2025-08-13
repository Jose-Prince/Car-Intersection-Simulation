#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cars.h"
#include "semaphore.h"
#include "intersection.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Insuficients parameters, need: ticks (1) and grid size (2)");
    return 1;
  }

  int ticks = atoi(argv[1]);
  int size = atoi(argv[2]);

  ArrayList* cars = createArrayList(1);
  Semaphore* semaphores = initializeSemaphore();
  Intersection* intersection = initializeIntersection(size);

  for (int i = 0; i < ticks; i++) {
    printIntersectionGrid(intersection, size);
    sleep(2);
  }

  printf("Hello World");

  freeArrayList(cars);
  freeIntersection(intersection, size);
  return 0;
}
