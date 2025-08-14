#include "semaphore.h"
#include <stddef.h>

// Definición de los estados del semáforo
#define GREEN 0;   // Luz verde: carro puede avanzar
#define YELLOW 1;  // Luz amarilla: advertencia de cambio de semáforo
#define RED 2;     // Luz roja: carro debe detenerse
#define PHASE_TICKS 12 // Número de ticks que dura cada fase del semáforo

// Inicializa los semáforos para los 4 carriles de la intersección
Semaphore* initializeSemaphore() {
  static Semaphore semaphores[4]; // Arreglo estático de 4 semáforos (uno por carril)
  
  // Inicializamos todos los semáforos en ROJO
  for (int i = 0; i < 4; i++) {
    semaphores[i].stateLeft = RED;
    semaphores[i].stateRight = RED;
    semaphores[i].stateStraight = RED;
  }

  // Definimos los semáforos iniciales en VERDE para algunos carriles
  semaphores[0].stateStraight = GREEN; // Carril 0: avance recto verde
  semaphores[0].stateRight = GREEN;    // Carril 0: giro a la derecha verde
  semaphores[2].stateStraight = GREEN; // Carril 2: avance recto verde
  semaphores[2].stateRight = GREEN;    // Carril 2: giro a la derecha verde

  return semaphores; // Retornamos puntero al arreglo de semáforos
}

// Cambia el estado de los semáforos según el tick actual
void changeState(int tick, Semaphore *semaphores) {
  // Determinamos la fase actual (0-3) según el número de ticks
  int phase = (tick / PHASE_TICKS) % 4;

  // Reiniciamos todos los semáforos a ROJO antes de activar los verdes
  for (int i = 0; i < 4; i++) {
    semaphores[i].stateStraight = RED;
    semaphores[i].stateRight = RED;
    semaphores[i].stateLeft = RED;
  }

  // Activamos los semáforos en verde según la fase actual
  switch (phase) {
    case 0: // Fase 0: carriles 0 y 2 recto y derecha en verde
      semaphores[0].stateStraight = GREEN;
      semaphores[0].stateRight = GREEN;
      semaphores[2].stateRight = GREEN;
      semaphores[2].stateStraight = GREEN;
      break;
    case 1: // Fase 1: carriles 1 y 3 recto y derecha en verde
      semaphores[1].stateStraight = GREEN;
      semaphores[1].stateRight    = GREEN;
      semaphores[3].stateStraight = GREEN;
      semaphores[3].stateRight    = GREEN;
      break;
    case 2: // Fase 2: carriles 0 y 2 giro a la izquierda en verde
      semaphores[0].stateLeft = GREEN;
      semaphores[2].stateLeft = GREEN;
      break;
    case 3: // Fase 3: carriles 1 y 3 giro a la izquierda en verde
      semaphores[1].stateLeft = GREEN;
      semaphores[3].stateLeft = GREEN;
      break;
  }
}

