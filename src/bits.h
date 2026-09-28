#ifndef BITS_H
#define BITS_H

// funciones para manejar las fichas de 3 bits dentro del bloque de bytes
int bytesNecesarios(int filas, int columnas);
unsigned char leerFicha(unsigned char* tablero, int pos);
void escribirFicha(unsigned char* tablero, int pos, unsigned char valor);
void mostrarBinario(unsigned char* tablero, int nBytes);

#endif
