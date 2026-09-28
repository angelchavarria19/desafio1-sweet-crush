#include <iostream>
#include "bits.h"
using namespace std;

int bytesNecesarios(int filas, int columnas)
{
    int bits = filas * columnas * 3;
    return (bits + 7) >> 3; // dividir entre 8 redondeando hacia arriba
}

// pos es la posicion logica (fila*columnas + columna)
unsigned char leerFicha(unsigned char* tablero, int pos)
{
    int bit = pos * 3;
    int byte = bit >> 3;   // bit / 8
    int desp = bit & 7;    // bit % 8

    unsigned char valor = tablero[byte] >> desp;
    if (desp > 5) {
        // la ficha quedo partida, el resto de bits esta en el siguiente byte
        valor = valor | (tablero[byte + 1] << (8 - desp));
    }
    return valor & 7;
}

void escribirFicha(unsigned char* tablero, int pos, unsigned char valor)
{
    int bit = pos * 3;
    int byte = bit >> 3;
    int desp = bit & 7;
    valor = valor & 7;

    // primero borro los bits viejos y despues pongo los nuevos
    tablero[byte] = tablero[byte] & ~(7 << desp);
    tablero[byte] = tablero[byte] | (valor << desp);

    if (desp > 5) {
        int quedan = 8 - desp; // cuantos bits alcanzaron a quedar en el primer byte
        tablero[byte + 1] = tablero[byte + 1] & ~(7 >> quedan);
        tablero[byte + 1] = tablero[byte + 1] | (valor >> quedan);
    }
}

void mostrarBinario(unsigned char* tablero, int nBytes)
{
    cout << "Memoria (" << nBytes << " bytes):" << endl;
    for (int i = 0; i < nBytes; i++) {
        cout << "B" << i << ": ";
        for (int b = 7; b >= 0; b--) {
            cout << ((tablero[i] >> b) & 1);
        }
        cout << "   ";
        if (i % 4 == 3) cout << endl;
    }
    cout << endl;
}
