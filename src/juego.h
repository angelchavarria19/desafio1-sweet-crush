#ifndef JUEGO_H
#define JUEGO_H

// posiciones del arreglo estado
const int ELIMINACIONES = 0;
const int FICHAS_ELIMINADAS = 1;
const int COMBINACIONES = 2;
const int CASCADAS = 3;
const int PUNTAJE = 4;

int buscarCombinaciones(unsigned char* t, int filas, int columnas, int* estado);
void quitarMarcadas(unsigned char* t, int filas, int columnas);
void bajarFichas(unsigned char* t, int filas, int columnas);
void rellenar(unsigned char* t, int filas, int columnas);
void resolverTablero(unsigned char* t, int filas, int columnas, int* estado, bool mostrar);
void eliminarFicha(unsigned char* t, int filas, int columnas, int f, int c, int* estado);
void mostrarEstado(int filas, int columnas, int reservados, int* estado);

#endif
