#include "cars.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "intersection.h"

static const size_t STRAIGHT = 0;
static const size_t RIGHT = 1;
static const size_t LEFT = 2;

double generateVelocity();

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
        if (j > lane1 && j < mid && (rand() % 100 > 50) && intersection->grid[0][j] != 'O') {
            intersection->grid[0][j] = 'O'; // primera fila
            Car newCar;
            newCar.mode = STRAIGHT;
            newCar.pos[0] = 0;
            newCar.pos[1] = j;
            newCar.velocity = generateVelocity();
            newCar.initialLane = 1;
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
            insert(arr, newCar);
        }
    }
}

void move(Car* car, Intersection* intersection) {
    int x = car->pos[0]; // fila
    int y = car->pos[1]; // columna

    // Borra la posición antigua
    if (x >= 0 && x < intersection->size && y >= 0 && y < intersection->size)
        intersection->grid[x][y] = ' ';

    int newX = x;
    int newY = y;

    // Mueve según carril
    if (car->initialLane == 1) newX += 1;     // hacia abajo
    else if (car->initialLane == 3) newY -= 1; // hacia derecha
    else if (car->initialLane == 5) newX -= 1; // hacia arriba
    else if (car->initialLane == 7) newY += 1; // hacia izquierda

    // Verifica límites antes de dibujar
    if (newX >= 0 && newX < intersection->size &&
        newY >= 0 && newY < intersection->size) {
        car->pos[0] = newX;
        car->pos[1] = newY;
        intersection->grid[newX][newY] = 'O';
    } else {
        // opcional: el carro llegó al borde, se puede eliminar o detener
        // por ejemplo:
        // car->active = 0;
    }
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
