#ifndef TABLERO_H
#define TABLERO_H

// codigos: 0 = vacio, 1..6 = fichas, 7 = marcada para eliminar

void ponerSemilla(unsigned int s);
unsigned char fichaAleatoria();

unsigned char* crearTablero(int filas, int columnas);
void llenarTablero(unsigned char* t, int filas, int columnas);
void mostrarTablero(unsigned char* t, int filas, int columnas);

unsigned char leerPos(unsigned char* t, int columnas, int f, int c);
void escribirPos(unsigned char* t, int columnas, int f, int c, unsigned char v);

// filas y columnas (cambian el bloque de memoria)
void agregarFila(unsigned char*& t, int& filas, int columnas, int& reservados, int pos);
void eliminarFila(unsigned char*& t, int& filas, int columnas, int& reservados, int pos);
void agregarColumna(unsigned char*& t, int filas, int& columnas, int& reservados, int pos);
void eliminarColumna(unsigned char*& t, int filas, int& columnas, int& reservados, int pos);

#endif
