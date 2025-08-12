#include "intersection.h"
#include <stdlib.h>
#include <string.h>

Intersection* initializeIntersection(int size) {
  Intersection* intersection = malloc(sizeof(Intersection));
  if (!intersection) return NULL;

  intersection->grid = malloc(size * sizeof(char*));
  if (!intersection->grid) {
    free(intersection);
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    intersection->grid[i] = malloc(size * sizeof(char));
    for (int j = 0; j < size; j++) {
      intersection->grid[i][j] = ' ';
    }
  }

  return intersection;
}

void updateIntersection(Intersection* intersection, int old_pos[2], int new_pos[2]) {
  intersection->grid[old_pos[1]][old_pos[0]] = ' ';
  intersection->grid[new_pos[1]][new_pos[0]] = 'O';
}

void freeIntersection(Intersection* intersection, int size) {
  for (int i = 0; i < size; i++) {
    free(intersection->grid[i]);
  }

  free(intersection->grid);

  free(intersection);
}
