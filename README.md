# Sweet Crush - Desafío I

Informática II - 2026-2 - Universidad de Antioquia

Autor: (poner nombre y cédula)

## Qué hace

Es el juego Sweet Crush en consola hecho en C++ con Qt. El tablero se guarda en un bloque
de bytes (`unsigned char*`) y cada ficha ocupa 3 bits, pegadas una detrás de otra.

Se puede:
- crear el tablero con fichas aleatorias
- ver el tablero en fichas y en binario
- eliminar una ficha
- buscar combinaciones de 3 o más (horizontal y vertical)
- bajar fichas, rellenar y seguir con las cascadas
- agregar / eliminar filas y columnas en cualquier posición
- ver el estado (eliminaciones, fichas, combinaciones, cascadas, puntaje)

## Códigos de las fichas

| código | qué es | se ve como |
|---|---|---|
| 000 | vacío | `.` |
| 001 a 110 | fichas 1 a 6 | `1` a `6` |
| 111 | marcada para eliminar | `*` |

El vacío es 000 porque al crear el bloque en ceros ya queda todo vacío, y los bits que sobran
al final también quedan en cero.

## Fórmulas

- posición = fila * columnas + columna
- bit inicial = posición * 3
- byte = bit >> 3
- desplazamiento = bit & 7
- si el desplazamiento es mayor que 5 la ficha queda partida entre dos bytes
- bytes = (3 * filas * columnas + 7) / 8

Al eliminar filas o columnas solo se pide un bloque nuevo si lo usado baja del 65% de lo
reservado, si no se reacomoda en el mismo bloque.

## Puntaje

- 1 punto por la ficha que elimina el usuario
- 10 puntos por cada ficha de una combinación, multiplicado por la ronda
  (ronda 1 = x1, primera cascada = x2, etc.)

## Archivos

- `src/bits.cpp` - leer y escribir fichas de 3 bits, mostrar binario
- `src/tablero.cpp` - crear, mostrar, filas y columnas
- `src/juego.cpp` - combinaciones, caída, cascadas y estado
- `src/main.cpp` - menú
- `docs/` - enunciado, hojas del análisis, bitácora

## Cómo correrlo

Abrir `src/SweetCrush.pro` en Qt Creator y darle Run.
