#ifndef CARS_H
#define CARS_H

#include "intersection.h"

typedef struct {
  int pos[2];
  double velocity;
  int mode;
  int initialLane;
} Car;

typedef struct {
  Car* data;
  int size;
  int capacity;
} ArrayList;

ArrayList* createArrayList(int initialCapacity);
void insert(ArrayList* arr, Car value);
void removeAt(ArrayList* arr, int index);
void removeAtPosition(ArrayList* arr, int x, int y);
void freeArrayList(ArrayList* arr);
void enterCars(Intersection* intersection, ArrayList* arr);
void move(Car* car, Intersection* intersection);

#endif
