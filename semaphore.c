#include "semaphore.h"
#include <stddef.h>
#include <stdio.h>

static const size_t GREEN = 0;
static const size_t YELLOW = 1;
static const size_t RED = 2;

Semaphore* initializeSemaphore() {
  static Semaphore semaphores[4];
  
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      semaphores[i].stateLeft = GREEN;
      semaphores[i].stateRight = GREEN;
      semaphores[i].stateStraight = GREEN;
    }

    semaphores[i].stateLeft = RED;
    semaphores[i].stateRight = RED;
    semaphores[i].stateStraight = RED;

  }

  return semaphores;
}

void changeState(int tick, Semaphore *semaphores) {
  for (int i = 0; i < 4; i++) {
    // TODO: make action for changing semaphore
  }
}
