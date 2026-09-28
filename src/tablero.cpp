#include <iostream>
#include "tablero.h"
#include "bits.h"
using namespace std;

static unsigned int semilla = 1;

void ponerSemilla(unsigned int s)
{
    semilla = s;
}

// generador congruencial lineal, devuelve de 1 a 6
unsigned char fichaAleatoria()
{
    semilla = semilla * 1103515245 + 12345;
    return ((semilla >> 16) % 6) + 1;
}

unsigned char* crearTablero(int filas, int columnas)
{
    int n = bytesNecesarios(filas, columnas);
    unsigned char* t = new unsigned char[n];
    for (int i = 0; i < n; i++) t[i] = 0; // todo vacio (000)
    return t;
}

void llenarTablero(unsigned char* t, int filas, int columnas)
{
    for (int i = 0; i < filas * columnas; i++) {
        escribirFicha(t, i, fichaAleatoria());
    }
}

unsigned char leerPos(unsigned char* t, int columnas, int f, int c)
{
    return leerFicha(t, f * columnas + c);
}

void escribirPos(unsigned char* t, int columnas, int f, int c, unsigned char v)
{
    escribirFicha(t, f * columnas + c, v);
}

void mostrarTablero(unsigned char* t, int filas, int columnas)
{
    cout << "    ";
    for (int c = 0; c < columnas; c++) cout << c % 10 << " ";
    cout << endl;
    for (int f = 0; f < filas; f++) {
        if (f < 10) cout << " ";
        cout << f << "  ";
        for (int c = 0; c < columnas; c++) {
            unsigned char v = leerPos(t, columnas, f, c);
            if (v == 0) cout << ". ";
            else if (v == 7) cout << "* ";
            else cout << (char)('0' + v) << " ";
        }
        cout << endl;
    }
}

void agregarFila(unsigned char*& t, int& filas, int columnas, int& reservados, int pos)
{
    unsigned char* nuevo = crearTablero(filas + 1, columnas);
    for (int f = 0; f < filas + 1; f++) {
        for (int c = 0; c < columnas; c++) {
            unsigned char v;
            if (f < pos) v = leerPos(t, columnas, f, c);
            else if (f == pos) v = fichaAleatoria();
            else v = leerPos(t, columnas, f - 1, c);
            escribirPos(nuevo, columnas, f, c, v);
        }
    }
    delete[] t;
    t = nuevo;
    filas++;
    reservados = bytesNecesarios(filas, columnas);
}

void agregarColumna(unsigned char*& t, int filas, int& columnas, int& reservados, int pos)
{
    int nc = columnas + 1;
    unsigned char* nuevo = crearTablero(filas, nc);
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < nc; c++) {
            unsigned char v;
            if (c < pos) v = leerPos(t, columnas, f, c);
            else if (c == pos) v = fichaAleatoria();
            else v = leerPos(t, columnas, f, c - 1);
            escribirPos(nuevo, nc, f, c, v);
        }
    }
    delete[] t;
    t = nuevo;
    columnas = nc;
    reservados = bytesNecesarios(filas, columnas);
}

// al eliminar solo se pide memoria nueva si el uso baja del 65%,
// si no se reacomoda dentro del mismo bloque
void eliminarFila(unsigned char*& t, int& filas, int columnas, int& reservados, int pos)
{
    int nf = filas - 1;
    int usados = bytesNecesarios(nf, columnas);
    unsigned char* destino = t;
    if (usados * 100 < reservados * 65) {
        destino = crearTablero(nf, columnas);
    }

    // se copia de adelante hacia atras, el indice nuevo nunca es mayor que el viejo
    for (int f = 0; f < nf; f++) {
        int origen = f;
        if (f >= pos) origen = f + 1;
        for (int c = 0; c < columnas; c++) {
            escribirPos(destino, columnas, f, c, leerPos(t, columnas, origen, c));
        }
    }

    if (destino != t) {
        delete[] t;
        t = destino;
        reservados = usados;
    } else {
        // limpio lo que sobro para que los bits vacios queden en cero
        for (int p = nf * columnas; p < filas * columnas; p++) escribirFicha(t, p, 0);
    }
    filas = nf;
}

void eliminarColumna(unsigned char*& t, int filas, int& columnas, int& reservados, int pos)
{
    int nc = columnas - 1;
    int usados = bytesNecesarios(filas, nc);
    unsigned char* destino = t;
    if (usados * 100 < reservados * 65) {
        destino = crearTablero(filas, nc);
    }

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < nc; c++) {
            int origen = c;
            if (c >= pos) origen = c + 1;
            escribirPos(destino, nc, f, c, leerPos(t, columnas, f, origen));
        }
    }

    if (destino != t) {
        delete[] t;
        t = destino;
        reservados = usados;
    } else {
        for (int p = filas * nc; p < filas * columnas; p++) escribirFicha(t, p, 0);
    }
    columnas = nc;
}
