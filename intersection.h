#ifndef INTERSECTION_H
#define INTERSECTION_H

typedef struct {
  char** grid;
  int size;
} Intersection;

Intersection* initializeIntersection(int size);
void updateIntersection(Intersection* intersection, int old_pos[2], int new_pos[2]);
void freeIntersection(Intersection* intersection, int size);
void printIntersectionGrid(Intersection* intersection);

#endif
