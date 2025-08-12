#ifndef CARS_H
#define CARS_H

typedef struct {
  int pos[2];
  float velocity;
  int turn;
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

#endif
