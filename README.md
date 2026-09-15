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

| Código | Binario | Significado |
|---|---|---|
| 0 | `000` | _(pendiente de definir)_ |
| 1 | `001` | _(pendiente)_ |
| 2 | `010` | _(pendiente)_ |
| 3 | `011` | _(pendiente)_ |
| 4 | `100` | _(pendiente)_ |
| 5 | `101` | _(pendiente)_ |
| 6 | `110` | _(pendiente)_ |
| 7 | `111` | _(pendiente)_ |

> Seis códigos representan las seis fichas del juego; los dos restantes quedan libres para
> estados auxiliares. La asignación concreta y su justificación se documentan aquí una vez
> tomada la decisión en la fase de análisis.

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
