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

  enterCars(intersection, cars);
  printIntersectionGrid(intersection);
  for (int i = 0; i < cars->size; i++) {
      Car car = cars->data[i];
      printf("x%d: %d, y%d: %d\n", i, car.pos[0], i, car.pos[1]);
    }
  sleep(2);

  for (int i = 0; i < ticks; i++) {
    enterCars(intersection, cars);
    for (int i = 0; i < cars->size; i++) {
      move(&cars->data[i], intersection);
    }
    printIntersectionGrid(intersection);
    for (int i = 0; i < cars->size; i++) {
      Car car = cars->data[i];
      printf("x%d: %d, y%d: %d\n", i, car.pos[0], i, car.pos[1]);
    }
    sleep(2);
  }

  printIntersectionGrid(intersection);
 
  freeArrayList(cars);
  freeIntersection(intersection, size);
  return 0;
}
