#include "structures.h"
#include <stdio.h>
#include <stdlib.h>

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
