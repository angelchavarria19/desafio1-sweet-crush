#include <iostream>
#include "juego.h"
#include "tablero.h"
#include "bits.h"
using namespace std;

// mapa de marcas: 1 bit por posicion
static void marcar(unsigned char* marcas, int p)
{
    marcas[p >> 3] = marcas[p >> 3] | (1 << (p & 7));
}

static bool estaMarcada(unsigned char* marcas, int p)
{
    return (marcas[p >> 3] >> (p & 7)) & 1;
}

// busca combinaciones de 3 o mas, las pone en 7 (*) y devuelve cuantas fichas marco
int buscarCombinaciones(unsigned char* t, int filas, int columnas, int* estado)
{
    int n = filas * columnas;
    int nMarcas = (n + 7) >> 3;
    unsigned char* marcas = new unsigned char[nMarcas];
    for (int i = 0; i < nMarcas; i++) marcas[i] = 0;

    // horizontales
    for (int f = 0; f < filas; f++) {
        int inicio = 0;
        for (int c = 1; c < columnas; c++) {
            if (leerPos(t, columnas, f, c) != leerPos(t, columnas, f, inicio)) {
                if (c - inicio >= 3 && leerPos(t, columnas, f, inicio) != 0) {
                    for (int k = inicio; k < c; k++) marcar(marcas, f * columnas + k);
                    estado[COMBINACIONES]++;
                }
                inicio = c;
            }
        }
    }

    // verticales
    for (int c = 0; c < columnas; c++) {
        int inicio = 0;
        for (int f = 1; f <= filas; f++) {
            if (f == filas || leerPos(t, columnas, f, c) != leerPos(t, columnas, inicio, c)) {
                if (f - inicio >= 3 && leerPos(t, columnas, inicio, c) != 0) {
                    for (int k = inicio; k < f; k++) marcar(marcas, k * columnas + c);
                    estado[COMBINACIONES]++;
                }
                inicio = f;
            }
        }
    }

    // se marcan al final para que una ficha que esta en horizontal y vertical cuente una vez
    int cuantas = 0;
    for (int p = 0; p < n; p++) {
        if (estaMarcada(marcas, p)) {
            escribirFicha(t, p, 7);
            cuantas++;
        }
    }
    delete[] marcas;
    return cuantas;
}

void quitarMarcadas(unsigned char* t, int filas, int columnas)
{
    for (int p = 0; p < filas * columnas; p++) {
        if (leerFicha(t, p) == 7) escribirFicha(t, p, 0);
    }
}

// por cada columna se recorre desde abajo y las fichas bajan a llenar los huecos
void bajarFichas(unsigned char* t, int filas, int columnas)
{
    for (int c = 0; c < columnas; c++) {
        int abajo = filas - 1;
        for (int f = filas - 1; f >= 0; f--) {
            unsigned char v = leerPos(t, columnas, f, c);
            if (v != 0) {
                if (f != abajo) {
                    escribirPos(t, columnas, abajo, c, v);
                    escribirPos(t, columnas, f, c, 0);
                }
                abajo--;
            }
        }
    }
}

void rellenar(unsigned char* t, int filas, int columnas)
{
    for (int p = 0; p < filas * columnas; p++) {
        if (leerFicha(t, p) == 0) escribirFicha(t, p, fichaAleatoria());
    }
}

// repite: buscar -> quitar -> bajar -> rellenar hasta que no haya combinaciones
// puntaje: 10 puntos por ficha multiplicado por el numero de ronda
void resolverTablero(unsigned char* t, int filas, int columnas, int* estado, bool mostrar)
{
    int ronda = 0;
    while (true) {
        int cuantas = buscarCombinaciones(t, filas, columnas, estado);
        if (cuantas == 0) break;
        ronda++;
        if (mostrar) {
            cout << endl << "Ronda " << ronda << ": se eliminan " << cuantas << " fichas" << endl;
            mostrarTablero(t, filas, columnas);
        }
        quitarMarcadas(t, filas, columnas);
        bajarFichas(t, filas, columnas);
        rellenar(t, filas, columnas);
        estado[FICHAS_ELIMINADAS] += cuantas;
        estado[PUNTAJE] += cuantas * 10 * ronda;
    }
    // la primera ronda es la combinacion normal, las demas son cascadas
    if (ronda > 1) estado[CASCADAS] = ronda - 1;
    else estado[CASCADAS] = 0;

    if (mostrar && ronda > 0) {
        cout << endl << "Tablero despues de resolver:" << endl;
        mostrarTablero(t, filas, columnas);
    }
}

void eliminarFicha(unsigned char* t, int filas, int columnas, int f, int c, int* estado)
{
    escribirPos(t, columnas, f, c, 0);
    estado[ELIMINACIONES]++;
    estado[FICHAS_ELIMINADAS]++;
    estado[PUNTAJE] += 1;
    bajarFichas(t, filas, columnas);
    rellenar(t, filas, columnas);
    cout << "Tablero despues de eliminar (" << f << "," << c << "):" << endl;
    mostrarTablero(t, filas, columnas);
    resolverTablero(t, filas, columnas, estado, true);
}

void mostrarEstado(int filas, int columnas, int reservados, int* estado)
{
    cout << "---- Estado ----" << endl;
    cout << "Tablero: " << filas << " x " << columnas << endl;
    cout << "Bytes usados: " << bytesNecesarios(filas, columnas)
         << "  reservados: " << reservados << endl;
    cout << "Eliminaciones del usuario: " << estado[ELIMINACIONES] << endl;
    cout << "Fichas eliminadas: " << estado[FICHAS_ELIMINADAS] << endl;
    cout << "Combinaciones: " << estado[COMBINACIONES] << endl;
    cout << "Cascadas (ultima jugada): " << estado[CASCADAS] << endl;
    cout << "Puntaje: " << estado[PUNTAJE] << endl;
}
