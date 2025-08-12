#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct {
  int stateStraight;
  int stateRight;
  int stateLeft;
} Semaphore;

Semaphore* initializeSemaphore();
void changeState(int tick, Semaphore* semaphores);

#endif
