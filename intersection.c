#include "intersection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inicializa la intersección con un grid de tamaño `size x size`
Intersection* initializeIntersection(int size) {
    // Reservamos memoria para la estructura Intersection
    Intersection* intersection = malloc(sizeof(Intersection));
    if (!intersection) return NULL;

    // Reservamos memoria para las filas del grid (arreglo de punteros)
    intersection->grid = malloc(size * sizeof(char*));
    if (!intersection->grid) {
        free(intersection);
        return NULL;
    }

    // Definimos posiciones clave de carriles y centro
    int lane1 = 2;           // Segunda columna/fila
    int lane2 = size - 3;    // Penúltima columna/fila
    int mid = size / 2;      // Centro de la intersección
    
    int innerSize = size - 6;           // Tamaño del área interna de la intersección
    int start = (size - innerSize) / 2; // Inicio de la zona libre
    int end = start + innerSize - 1;    // Fin de la zona libre

    // **Paralelizamos la inicialización del grid**
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        intersection->grid[i] = malloc(size * sizeof(char));
        for (int j = 0; j < size; j++) {
            // Zona interna libre
            if (i >= start && i <= end && j >= start && j <= end) {
                intersection->grid[i][j] = ' ';
            } 
            // Intersección de carriles
            else if ((j == lane1 || j == lane2 || j == mid) && 
                     (i == lane1 || i == lane2 || i == mid)) {
                intersection->grid[i][j] = '+';
            } 
            // Carriles verticales
            else if (j == lane1 || j == lane2 || j == mid) {
                intersection->grid[i][j] = '|';
            } 
            // Carriles horizontales
            else if (i == lane1 || i == lane2 || i == mid) {
                intersection->grid[i][j] = '-';
            } 
            // Resto del grid vacío
            else {
                intersection->grid[i][j] = ' ';
            }
        }
    }

    // **Paralelizamos limpieza horizontal entre '+'**
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        int lastPlus = -1;
        for (int j = 0; j < size; j++) {
            if (intersection->grid[i][j] == '+') {
                if (lastPlus != -1) {
                    // Limpiamos espacio entre '+' horizontalmente
                    for (int k = lastPlus + 1; k < j; k++) {
                        intersection->grid[i][k] = ' ';
                    }
                }
                lastPlus = j;
            }
        }
    }

    // Limpieza vertical entre '+'
    for (int j = 0; j < size; j++) {
        int lastPlus = -1;
        for (int i = 0; i < size; i++) {
            if (intersection->grid[i][j] == '+') {
                if (lastPlus != -1) {
                    // Limpiamos espacio entre '+' verticalmente
                    for (int k = lastPlus + 1; k < i; k++) {
                        intersection->grid[k][j] = ' ';
                    }
                }
                lastPlus = i;
            }
        }
    }

    // Guardamos el tamaño de la intersección
    intersection->size = size;

    return intersection;
}

// Actualiza la posición de un carro en el grid
void updateIntersection(Intersection* intersection, int old_pos[2], int new_pos[2]) {
  intersection->grid[old_pos[1]][old_pos[0]] = ' '; // Limpiamos posición anterior
  intersection->grid[new_pos[1]][new_pos[0]] = 'O'; // Marcamos posición nueva
}

// Libera la memoria ocupada por el grid y la estructura
void freeIntersection(Intersection* intersection, int size) {
  for (int i = 0; i < size; i++) {
    free(intersection->grid[i]); // Liberamos cada fila
  }

  free(intersection->grid); // Liberamos el arreglo de punteros
  free(intersection);       // Liberamos la estructura
}

// Imprime el grid de la intersección
void printIntersectionGrid(Intersection* intersection) {
  system("clear"); // Limpiamos pantalla
  for (int i = 0; i < intersection->size; i++) {
    for (int j = 0; j < intersection->size; j++) {
      printf("%c ", intersection->grid[i][j]); // Imprimimos cada celda
    }
    printf("\n");
  }
}

