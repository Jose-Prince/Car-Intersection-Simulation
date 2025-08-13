#include "cars.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"

static const size_t STRAIGHT = 0;
static const size_t RIGHT = 1;
static const size_t LEFT = 2;

static const size_t GREEN = 0;
static const size_t YELLOW = 1;
static const size_t RED = 2;

double generateVelocity();
void determineTarget(Car* car, Intersection* intersection);

ArrayList* createArrayList(int initialCapacity) {
  ArrayList* arr = (ArrayList*)malloc(sizeof(ArrayList));
  if (arr == NULL) {
    perror("Failed to allocate ArrayList");
    return NULL;
  }
  arr->data = (Car*)malloc(initialCapacity * sizeof(Car));
  if (arr->data == NULL) {
    perror("Failed to allocate data array");
    free(arr);
    return NULL;
  }
  arr->size = 0;
  arr->capacity = initialCapacity;
  return arr;
}

void insert(ArrayList *arr, Car value) {
  if (arr->size == arr->capacity) {
    arr->capacity *= 2;
    Car* newData = (Car*)realloc(arr->data, arr->capacity * sizeof(Car));
    if (newData == NULL) {
      perror("failed to reallocate data array");
      return;
    }
    arr->data = newData;
  }
  arr->data[arr->size++] = value;
}

void removeAt(ArrayList* arr, int index) {
  if (index < 0 || index >= arr->size) {
    fprintf(stderr, "Index otu of bounds: %d\n", index); 
    return;
  }

  for (int i = index; i < arr->size - 1; i++) {
    arr->data[i] = arr->data[i + 1];
  }

  arr->size--;
}

void removeAtPosition(ArrayList* arr, int x, int y) {
  for (int i = 0; i < arr->size; i++) {
    if (arr->data[i].pos[0] == x && arr->data[i].pos[1] == y) {
      removeAt(arr, i);
      return;
    }
  }
}

void freeArrayList(ArrayList *arr) {
  if (arr != NULL) {
    free(arr->data);
    free(arr);
  }
}

void enterCars(Intersection* intersection, ArrayList* arr) {
    int lane1 = 2;
    int lane2 = intersection->size - 3;
    int mid = intersection->size / 2;

    // Carros entrando desde arriba (verticales)
    for (int j = 0; j < intersection->size; j++) {
        if (j > lane1 && j < mid && (rand() % 100 > 90) && intersection->grid[0][j] != 'O') {
            intersection->grid[0][j] = 'O'; // primera fila
            Car newCar;
            newCar.mode = STRAIGHT;
            newCar.pos[0] = 0;
            newCar.pos[1] = j;
            newCar.velocity = generateVelocity();
            newCar.initialLane = 1;
            newCar.target[0] = 0;
            newCar.target[1] = 0;
            newCar.advance = 0;
            insert(arr, newCar);
        }
    }

    // Carros entrando desde abajo (verticales)
    for (int j = 0; j < intersection->size; j++) {
        if (j < lane2 && j > mid && (rand() % 100 > 50) && intersection->grid[intersection->size - 1][j] != 'O') {
            intersection->grid[intersection->size - 1][j] = 'O'; // última fila
            Car newCar;
            newCar.mode = STRAIGHT;
            newCar.pos[0] = intersection->size - 1;
            newCar.pos[1] = j;
            newCar.velocity = generateVelocity();
            newCar.initialLane = 5;
            newCar.target[0] = 0;
            newCar.target[1] = 0;
            newCar.advance = 0;
            insert(arr, newCar);
        }
    }

    // Carros entrando desde la izquierda (horizontales)
    for (int i = 0; i < intersection->size; i++) {
        if (i < lane2 && i > mid && (rand() % 100 > 50) && intersection->grid[i][0] != 'O') {
            intersection->grid[i][0] = 'O'; // primera columna
            Car newCar;
            newCar.mode = STRAIGHT;
            newCar.pos[0] = i;
            newCar.pos[1] = 0;
            newCar.velocity = generateVelocity();
            newCar.initialLane = 7;
            newCar.target[0] = 0;
            newCar.target[1] = 0;
            newCar.advance = 0;
            insert(arr, newCar);
        }
    }

    // Carros entrando desde la derecha (horizontales)
    for (int i = 0; i < intersection->size; i++) {
        if (i > lane1 && i < mid && (rand() % 100 > 50) && intersection->grid[i][intersection->size - 1] != 'O') {
            intersection->grid[i][intersection->size - 1] = 'O'; // última columna
            Car newCar;
            newCar.mode = STRAIGHT;
            newCar.pos[0] = i;
            newCar.pos[1] = intersection->size - 1;
            newCar.velocity = generateVelocity();
            newCar.initialLane = 3;
            newCar.target[0] = 0;
            newCar.target[1] = 0;
            newCar.advance = 0;
            insert(arr, newCar);
        }
    }
}

void move(Car* car, Intersection* intersection, Semaphore* semaphores, ArrayList* arr) {
  int x = car->pos[0]; // fila
  int y = car->pos[1]; // columna
    
  int laneIndex;
  if (car->initialLane == 1) laneIndex = 0;
  else if (car->initialLane == 3) laneIndex = 1;
  else if (car->initialLane == 5) laneIndex = 2;
  else if (car->initialLane == 7) laneIndex = 3;
  else return;

  int allowed = 0;
  if (car->mode == STRAIGHT && semaphores[laneIndex].stateStraight == GREEN) allowed = 1;
  if (car->mode == RIGHT && semaphores[laneIndex].stateRight == GREEN) allowed = 1;
  if (car->mode == LEFT && semaphores[laneIndex].stateLeft == GREEN) allowed = 1;
  
  if (!allowed) {
    return;
  }

  int newX = x;
  int newY = y;

  if (car->initialLane == 1) newX += 1;     // hacia abajo
  else if (car->initialLane == 3) newY -= 1; // hacia derecha
  else if (car->initialLane == 5) newX -= 1; // hacia arriba
  else if (car->initialLane == 7) newY += 1; // hacia izquierda

  if (newX < 0 || newX >= intersection->size || newY < 0 || newY >= intersection->size) {
    removeAtPosition(arr, x, y);
    intersection->grid[x][y] = ' ';
    return;
  }

  if (intersection->grid[newX][newY] == 'O' || intersection->grid[newX][newY] == '|' || intersection->grid[newX][newY] == '-') {
    return;
  }

  if (x >= 0 && x < intersection->size && y >= 0 && y < intersection->size)
    intersection->grid[x][y] = ' ';

  car->pos[0] = newX;
  car->pos[1] = newY;
  car->advance += 1;

  if (car->advance == 3 && (car->target[0] == 0 && car->target[1] == 0)) {
    int option = rand() % 3;
    if (option == 1) car->mode = RIGHT;
    else if (option == 2) car->mode = LEFT;
    determineTarget(car, intersection);
  }

  intersection->grid[newX][newY] = 'O';
}

double generateVelocity() {
  int r = rand() % 3;

  double value;
  switch (r) {
    case 0: value = 0.3; break;
    case 1: value = 0.7; break;
    case 2: value = 1.0; break;
  }

  return value;
}

void determineTarget(Car* car, Intersection* intersection) {
  int s = intersection->size;
  int targets[4][3][2] = {
    // Lane 1 (de arriba hacia abajo)
    { {s-2, car->pos[1]},  // RIGHT
      {s/2, s-2},    // STRAIGHT
      {1, s/2+1} },  // LEFT

    // Lane 3 (de derecha a izquierda)
    { {s/2+1, s-2},  // RIGHT
      {1, s/2},      // STRAIGHT
      {s/2-1, 1} },  // LEFT

    // Lane 5 (de abajo a arriba)
    { {1, s/2+1},    // RIGHT
      {s/2, 1},      // STRAIGHT
      {s-2, s/2-1} },// LEFT

    // Lane 7 (de izquierda a derecha)
    { {s/2-1, 1},    // RIGHT
      {s-2, s/2},    // STRAIGHT
      {s/2+1, s-2} } // LEFT
    };
  int lane_index;
  if (car->initialLane == 1) lane_index = 0;
  else if (car->initialLane == 3) lane_index = 1;
  else if (car->initialLane == 5) lane_index = 2;
  else if (car->initialLane == 7) lane_index = 3;
  else return;

  car->target[0] = targets[lane_index][car->mode][0];
  car->target[1] = targets[lane_index][car->mode][1];
}

