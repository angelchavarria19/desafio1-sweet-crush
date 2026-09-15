# Sweet Crush — Desafío I

Implementación del juego **Sweet Crush** en C++ (Qt) usando **manipulación de bits** y
**memoria dinámica**, bajo restricciones de programación estructurada.

| | |
|---|---|
| **Curso** | Informática II |
| **Semestre** | 2026 – 2 |
| **Autor** | _(nombre completo y cédula)_ |
| **Universidad** | Universidad de Antioquia |
| **Fecha de entrega** | 18 de septiembre de 2026 |

---

## 1. Descripción del problema

El programa administra un tablero rectangular de fichas almacenado como una **secuencia
continua de bits**: cada posición del tablero ocupa **exactamente 3 bits**, sin alineación a
byte, de forma que una misma ficha puede quedar repartida entre dos bytes consecutivos.

Sobre esa representación compacta el programa debe:

- Crear un tablero de `F × C` con fichas aleatorias de distribución uniforme.
- Mostrar el tablero en **dos formatos**: fichas y volcado binario.
- Eliminar la ficha indicada por el usuario.
- Detectar combinaciones de 3 o más fichas iguales, **horizontales y verticales**,
  incluyendo el caso en que una ficha pertenece a ambas simultáneamente.
- Reorganizar el tablero (caída de fichas + generación de nuevas) y procesar **cascadas**
  hasta que no aparezcan más combinaciones.
- Agregar y eliminar filas y columnas **en cualquier posición**, incluidas las intermedias,
  modificando realmente la memoria reservada.
- Llevar el estado de la partida: dimensiones, eliminaciones, fichas eliminadas,
  combinaciones, cascadas y puntaje.

---

## 2. Restricciones de la solución

- C++ sobre **Qt**, sin sintaxis ANSI C (`printf`, `scanf`, `malloc`, `free`).
- **Prohibido**: `struct`, `class`, `template`, objetos definidos por el autor, `string`,
  la STL y cualquier estructura dinámica de biblioteca.
- Obligatorio el uso de **punteros, arreglos y memoria dinámica** en el núcleo.
- Obligatorio el uso de **operadores a nivel de bits** (`& | ^ ~ << >>`) en el núcleo.
- Diseño **modular multi-archivo** (`.h` / `.cpp`).
- Prohibido desempaquetar el tablero a una estructura auxiliar de un byte o entero por ficha.
- La memoria reservada corresponde a las dimensiones **actuales** del tablero; no se
  sobredimensiona ni se reserva para expansiones futuras.

---

## 3. Representación de los datos

### 3.1 Codificación de las fichas (3 bits)

| Código | Binario | Significado | En pantalla |
|---|---|---|---|
| 0 | `000` | Posición vacía | `.` |
| 1 | `001` | Ficha 1 | `1` |
| 2 | `010` | Ficha 2 | `2` |
| 3 | `011` | Ficha 3 | `3` |
| 4 | `100` | Ficha 4 | `4` |
| 5 | `101` | Ficha 5 | `5` |
| 6 | `110` | Ficha 6 | `6` |
| 7 | `111` | Marcada para eliminar | `*` |

**Por qué la posición vacía es `000`:**

1. Al reservar el bloque y ponerlo en ceros, el tablero queda vacío recorriendo **bytes**, no
   posiciones lógicas.
2. Verificar si una posición está vacía se reduce a comparar contra cero.
3. El enunciado obliga a agrupar los bits sobrantes a la izquierda de la trama, de modo que
   ese relleno existe siempre. Con `000` como vacío, el relleno **es** una zona vacía y no
   puede confundirse con una ficha; con cualquier otra codificación habría que tratarlo como
   un caso aparte.

**Por qué las fichas van de `001` a `110`:**

El código almacenado coincide con el número de la ficha, por lo que el generador aleatorio
produce directamente el valor que se escribe en memoria, sin tabla de conversión intermedia.
El carácter mostrado en pantalla es el mismo dígito, lo que permite contrastar a simple vista
la vista de fichas con la vista binaria. Además todos los caracteres ocupan un ancho fijo, lo
que mantiene alineadas las columnas del tablero.

**Por qué `111` significa "marcada para eliminar":**

Una combinación no puede eliminarse en el momento de detectarla, porque las mismas posiciones
todavía deben compararse en el barrido perpendicular. El proceso es entonces: barrido
horizontal, barrido vertical y, solo al final, marcado de todas las posiciones involucradas.
Así una ficha que pertenece simultáneamente a una combinación horizontal y a una vertical se
procesa una sola vez.

El estado marcado también permite **mostrar el tablero con las fichas condenadas visibles**
antes de que desaparezcan, lo cual hace comprensible la secuencia de eliminación. Como `111`
tiene sus tres bits en uno, marcar una posición es una operación `OR` con la máscara, sin
necesidad de limpiar previamente los bits anteriores.

### 3.2 De la posición lógica a la memoria

_(Completar con la fórmula derivada en el análisis: posición lógica → bit inicial → byte →
desplazamiento dentro del byte, y el tratamiento del caso en que la ficha queda partida
entre dos bytes.)_

### 3.3 Tamaño del bloque reservado

_(Completar: cálculo de la cantidad mínima de bytes para `F × C` posiciones de 3 bits, y la
regla de reducción de memoria al eliminar filas o columnas.)_

---

## 4. Estructura del repositorio

```
desafio1-sweet-crush/
├── README.md
├── docs/
│   ├── enunciado-desafio1.pdf   · enunciado original
│   ├── plan.md                  · plan de trabajo por fases
│   ├── bitacora.md              · problemas encontrados y decisiones tomadas
│   ├── analisis/                · bocetos, mapas de bits y algoritmos (fase de diseño)
│   └── informe/                 · informe preliminar y final
└── src/                         · código fuente (.h / .cpp) — desde la fase 2
```

---

## 5. Compilación y ejecución

_(Completar cuando exista el proyecto Qt.)_

---

## 6. Criterio de puntuación

_(Completar: el enunciado permite definirlo libremente, pero exige documentarlo.)_

---

## 7. Estado de avance

- [ ] Fase 0 — Montaje del repositorio
- [ ] Fase 1 — Análisis y diseño en papel
- [ ] Fase 2 — Módulo de bits
- [ ] Fase 3 — Creación y visualización del tablero
- [ ] Fase 4 — Eliminación y detección de combinaciones
- [ ] Fase 5 — Reorganización y cascadas
- [ ] Fase 6 — Filas y columnas dinámicas
- [ ] Fase 7 — Estado del juego, puntaje y menú
- [ ] Fase 8 — Informe final y video

---

## 8. Entregables

| Entregable | Enlace |
|---|---|
| Repositorio | _(pendiente)_ |
| Informe | `docs/informe/` |
| Video (YouTube) | _(pendiente)_ |
