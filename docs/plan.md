# Plan de trabajo — Desafío I

Regla de trabajo: **primero papel, después teclado.** Cada fase termina en un commit.
Nada se implementa sin que su algoritmo esté escrito a mano antes.

## Calendario

| Día | Fases | Resultado esperado |
|---|---|---|
| Lun 15 | 0 y 1 | Repositorio montado + análisis y diseño en papel |
| Mar 16 | 2 y 3 | Módulo de bits verificado + tablero que se crea y se muestra |
| Mié 17 | 4 y 5 | Eliminación, combinaciones y cascadas funcionando |
| Jue 18 | 6, 7 y 8 | Filas/columnas, estado, informe y video |

Si el tiempo aprieta, el orden de sacrificio va al revés del peso en la rúbrica:
bits (30%) y memoria (35%) sostienen todo lo demás, y filas/columnas intermedias son
obligatorias porque el video las exige explícitamente.

---

## Fase 0 — Montaje

- [x] Carpeta del proyecto y `git init`
- [ ] `git config user.email` con el correo institucional (solo en este repositorio)
- [x] `.gitignore` de Qt
- [x] `README.md` estructurado
- [ ] Repositorio **público** en GitHub y primer push

## Fase 1 — Análisis y diseño (a mano)

Cinco hojas, detalladas en `analisis/guia-hojas.md`:

1. Tabla de códigos de 3 bits
2. Mapa posición lógica → byte y bit (tablero 3×3 dibujado)
3. Diagrama de módulos
4. Pseudocódigo de las operaciones núcleo
5. Partida simulada a mano en un tablero 4×4

Entregable: fotos o escaneos en `analisis/`, y el informe preliminar en `informe/`.

## Fase 2 — Módulo de bits (`bits.h` / `bits.cpp`)

- `bytesNecesarios(filas, columnas)`
- `leerFicha(tablero, indice)` — resuelve el caso partido entre dos bytes
- `escribirFicha(tablero, indice, valor)` — limpia con máscara y escribe
- `mostrarBinario(tablero, cantidadBytes)`

Verificación: escribir 0..7 en las primeras posiciones, leerlos de vuelta y contrastar el
volcado binario contra la hoja 2. Si esto no cuadra, nada más va a cuadrar.

## Fase 3 — Tablero (`tablero.h` / `tablero.cpp`)

- Crear, destruir, llenar con fichas aleatorias
- Generador congruencial lineal propio, con semilla por teclado
- Vista de fichas y vista binaria

## Fase 4 — Eliminación y combinaciones (`juego.h` / `juego.cpp`)

- Eliminar la ficha indicada por el usuario
- Detección horizontal y vertical en pasadas separadas sobre un mapa de marcas de 1 bit
- Aplicación de las marcas al final, para resolver las combinaciones simultáneas

## Fase 5 — Reorganización y cascadas

- Caída de fichas por columna
- Generación de fichas nuevas
- Bucle de cascadas con su contador

## Fase 6 — Filas y columnas dinámicas

- Agregar y eliminar fila o columna en cualquier posición, incluida la intermedia
- Copia ficha por ficha al bloque nuevo
- Regla de reducción de memoria: solo cuando el uso cae por debajo del 65%

## Fase 7 — Estado, puntaje y menú

- Dimensiones, eliminaciones del usuario, fichas eliminadas, combinaciones, cascadas, puntaje
- Menú principal en `main.cpp`

## Fase 8 — Cierre

- Informe final (secciones a–e del enunciado)
- Video de 5 a 11 minutos con los casos obligatorios
- Modo demo con semilla fija para reproducir la cascada triple frente a la cámara
- Los dos enlaces en Ude@
