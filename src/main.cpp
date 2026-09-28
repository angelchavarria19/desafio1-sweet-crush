#include <iostream>
#include "bits.h"
#include "tablero.h"
#include "juego.h"
using namespace std;

int main()
{
    int filas, columnas;
    unsigned int s;

    cout << "=== SWEET CRUSH ===" << endl;
    cout << "Filas: ";
    cin >> filas;
    cout << "Columnas: ";
    cin >> columnas;
    if (filas < 3) filas = 3;
    if (columnas < 3) columnas = 3;
    cout << "Semilla (numero): ";
    cin >> s;
    ponerSemilla(s);

    unsigned char* tablero = crearTablero(filas, columnas);
    int reservados = bytesNecesarios(filas, columnas);
    llenarTablero(tablero, filas, columnas);

    int* estado = new int[5];
    for (int i = 0; i < 5; i++) estado[i] = 0;

    // si el tablero sale con combinaciones de una vez se quitan sin contar puntos
    resolverTablero(tablero, filas, columnas, estado, false);
    for (int i = 0; i < 5; i++) estado[i] = 0;

    int op = -1;
    while (op != 0) {
        cout << endl;
        mostrarTablero(tablero, filas, columnas);
        cout << endl;
        cout << "1. Eliminar ficha" << endl;
        cout << "2. Agregar fila" << endl;
        cout << "3. Eliminar fila" << endl;
        cout << "4. Agregar columna" << endl;
        cout << "5. Eliminar columna" << endl;
        cout << "6. Ver binario" << endl;
        cout << "7. Ver estado" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> op;

        if (op == 1) {
            int f, c;
            cout << "Fila y columna: ";
            cin >> f >> c;
            if (f >= 0 && f < filas && c >= 0 && c < columnas) {
                eliminarFicha(tablero, filas, columnas, f, c, estado);
            } else {
                cout << "Posicion invalida" << endl;
            }
        } else if (op == 2) {
            int p;
            cout << "Posicion de la nueva fila (0 a " << filas << "): ";
            cin >> p;
            if (p >= 0 && p <= filas) {
                agregarFila(tablero, filas, columnas, reservados, p);
                resolverTablero(tablero, filas, columnas, estado, true);
            } else cout << "Posicion invalida" << endl;
        } else if (op == 3) {
            int p;
            cout << "Fila a eliminar: ";
            cin >> p;
            if (filas > 1 && p >= 0 && p < filas) {
                eliminarFila(tablero, filas, columnas, reservados, p);
                resolverTablero(tablero, filas, columnas, estado, true);
            } else cout << "No se puede" << endl;
        } else if (op == 4) {
            int p;
            cout << "Posicion de la nueva columna (0 a " << columnas << "): ";
            cin >> p;
            if (p >= 0 && p <= columnas) {
                agregarColumna(tablero, filas, columnas, reservados, p);
                resolverTablero(tablero, filas, columnas, estado, true);
            } else cout << "Posicion invalida" << endl;
        } else if (op == 5) {
            int p;
            cout << "Columna a eliminar: ";
            cin >> p;
            if (columnas > 1 && p >= 0 && p < columnas) {
                eliminarColumna(tablero, filas, columnas, reservados, p);
                resolverTablero(tablero, filas, columnas, estado, true);
            } else cout << "No se puede" << endl;
        } else if (op == 6) {
            mostrarBinario(tablero, reservados);
        } else if (op == 7) {
            mostrarEstado(filas, columnas, reservados, estado);
        }
    }

    delete[] tablero;
    delete[] estado;
    cout << "Chao!" << endl;
    return 0;
}
