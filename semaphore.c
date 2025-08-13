#include "semaphore.h"
#include <stddef.h>

#define GREEN 0;
#define YELLOW 1;
#define RED 2;
#define PHASE_TICKS 12

Semaphore* initializeSemaphore() {
  static Semaphore semaphores[4];
  
  for (int i = 0; i < 4; i++) {
    semaphores[i].stateLeft = RED;
    semaphores[i].stateRight = RED;
    semaphores[i].stateStraight = RED;
  }

  semaphores[0].stateStraight = GREEN;
  semaphores[0].stateRight = GREEN;
  semaphores[2].stateStraight = GREEN;
  semaphores[2].stateRight = GREEN;

  return semaphores;
}

void changeState(int tick, Semaphore *semaphores) {
  int phase = (tick / PHASE_TICKS) % 4;

  for (int i = 0; i < 4; i++) {
    semaphores[i].stateStraight = RED;
    semaphores[i].stateRight = RED;
    semaphores[i].stateLeft = RED;
  }

  switch (phase) {
    case 0:
      semaphores[0].stateStraight = GREEN;
      semaphores[0].stateRight = GREEN;
      semaphores[2].stateRight = GREEN;
      semaphores[2].stateStraight = GREEN;
      break;
    case 1:
      semaphores[1].stateStraight = GREEN;
      semaphores[1].stateRight    = GREEN;
      semaphores[3].stateStraight = GREEN;
      semaphores[3].stateRight    = GREEN;
      break;
    case 2:
      semaphores[0].stateLeft = GREEN;
      semaphores[2].stateLeft = GREEN;
      break;
    case 3:
      semaphores[1].stateLeft = GREEN;
      semaphores[3].stateLeft = GREEN;
      break;
  }
}
