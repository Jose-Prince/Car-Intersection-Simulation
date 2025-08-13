#include "intersection.h"
#include <stdio.h>
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

    int lane1 = 2;           // segunda columna
    int lane2 = size - 3;    // penúltima columna
    int mid = size / 2;      // center of grid
    
    int innerSize = size - 6;
    int start = (size - innerSize) / 2;
    int end = start + innerSize - 1;

    for (int i = 0; i < size; i++) {
        intersection->grid[i] = malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            if (i >= start && i <= end && j >= start && j <= end) {
                intersection->grid[i][j] = ' ';
            } else if ((j == lane1 || j == lane2 || j == mid) && 
                (i == lane1 || i == lane2 || i == mid)) {
                intersection->grid[i][j] = '+';
            } else if (j == lane1 || j == lane2 || j == mid) {
                intersection->grid[i][j] = '|';
            } else if (i == lane1 || i == lane2 || i == mid) {
                intersection->grid[i][j] = '-';
            } else {
                intersection->grid[i][j] = ' ';
            }
        }
    }

    for (int i = 0; i < size; i++) {
        int lastPlus = -1;
        for (int j = 0; j < size; j++) {
            if (intersection->grid[i][j] == '+') {
                if (lastPlus != -1) {
                    for (int k = lastPlus + 1; k < j; k++) {
                        intersection->grid[i][k] = ' ';
                    }
                }
                lastPlus = j;
            }
        }
    }

    for (int j = 0; j < size; j++) {
        int lastPlus = -1;
        for (int i = 0; i < size; i++) {
            if (intersection->grid[i][j] == '+') {
                if (lastPlus != -1) {
                    for (int k = lastPlus + 1; k < i; k++) {
                        intersection->grid[k][j] = ' ';
                    }
                }
                lastPlus = i;
            }
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

void printIntersectionGrid(Intersection* intersection, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%c ", intersection->grid[i][j]);
    }
    printf("\n");
  }
}
