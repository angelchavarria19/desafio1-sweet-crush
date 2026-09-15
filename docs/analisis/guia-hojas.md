# Fase 1 — Guía de las cinco hojas

Esto se hace **a mano, en papel**, antes de escribir una línea de código. No es un trámite:
cada hoja aquí resuelve un pedazo del informe y una pregunta probable de la sustentación.
Cuando termines cada hoja, tómale foto y guárdala en esta carpeta.

---

## Hoja 1 — Tabla de códigos de 3 bits

Con 3 bits hay 8 combinaciones. Seis son fichas; dos quedan libres.

Dibuja la tabla completa (`000` a `111`) y decide:

- ¿Cuáles seis códigos son las fichas, y qué carácter la representa en pantalla?
- ¿Qué código representa una **posición vacía**?
- ¿Qué haces con el octavo código?

**Pregunta para pensar antes de decidir:** durante la detección de combinaciones vas a
necesitar señalar fichas que van a desaparecer, sin borrarlas todavía (porque aún tienes
que seguir comparando sus vecinas). ¿Te sirve para eso el octavo código, o prefieres
gastarlo en otra cosa?

**Para elegir los caracteres de pantalla:** que se distingan de un vistazo en una terminal
y que todos ocupen **el mismo ancho**, o las columnas del tablero se van a desalinear.

---

## Hoja 2 — El mapa: de la posición a la memoria

Esta es la hoja más importante de todo el desafío.

Dibuja un tablero de **3 filas × 3 columnas** (9 posiciones, 27 bits, 4 bytes).

Debajo, dibuja los 4 bytes como cuatro cajas de 8 casillas cada una, numerando los bits.
Recuerda la regla del enunciado: **la trama válida empieza en el bit menos significativo** y
los bits sobrantes se agrupan a la izquierda de toda la trama.

Ahora, para **cada una de las 9 posiciones**, completa a mano esta tabla:

| fila | columna | posición lógica | bit inicial | byte | desplazamiento | ¿partida? |
|---|---|---|---|---|---|---|
| 0 | 0 | | | | | |
| 0 | 1 | | | | | |
| … | | | | | | |

Las tres relaciones que tienes que **derivar tú** (no copiarlas):

- posición lógica a partir de fila y columna
- bit inicial a partir de la posición lógica
- byte y desplazamiento a partir del bit inicial

Y la pregunta central:

> **¿A partir de qué desplazamiento los 3 bits de una ficha ya no caben en el byte y se
> parten hacia el siguiente?** Míralo en tu dibujo, cuenta casillas, y escribe la condición.

Cuando encuentres una ficha partida, píntala de otro color y responde:

- ¿Cuántos bits quedan en el primer byte y cuántos pasan al segundo?
- Para **leerla**: ¿qué haces con los bits del primer byte y qué haces con los del segundo
  antes de juntarlos?
- Para **escribirla**: ¿cómo borras los bits viejos sin tocar los de las fichas vecinas?

Si esta hoja queda bien, el módulo de bits te va a salir casi solo. Si la saltas, vas a pasar
horas depurando y no vas a saber qué preguntarle al código.

**Verificación rápida:** para el tablero 3×3, ¿en qué byte y desplazamiento cae la posición
(2,2)? ¿Cuántos bits del último byte quedan sin usar? ¿Dónde quedan esos bits sobrantes?

---

## Hoja 3 — Diagrama de módulos

Cajas y flechas. Cuatro módulos, y dentro de cada uno la lista de funciones que expone su
`.h`:

```
   main.cpp  ──►  juego  ──►  tablero  ──►  bits  ──►  memoria (unsigned char *)
```

Para cada función anota: **qué recibe, qué devuelve, y qué modifica.**

Dos preguntas de diseño que tienes que resolver en esta hoja, porque el enunciado prohíbe
`struct` y `class`:

1. El tablero son tres datos que viajan siempre juntos: el puntero, las filas y las columnas.
   Sin `struct`, ¿cómo los pasas entre funciones? ¿Y cómo haces para que una función que
   **reemplaza** el bloque de memoria (agregar fila) deje al llamador viendo el bloque nuevo?
2. El estado del juego son seis contadores. ¿Variables sueltas, un arreglo de enteros con
   índices nombrados por constantes, o algo más? Argumenta la decisión: la rúbrica evalúa
   explícitamente que la elección de tipos y estructuras esté justificada.

---

## Hoja 4 — Pseudocódigo

En español, sin sintaxis de C++. Una hoja para estos seis algoritmos:

1. **leerFicha(posición)** — incluyendo el caso partido entre dos bytes
2. **escribirFicha(posición, valor)** — incluyendo el borrado con máscara
3. **detectarCombinaciones** — ¿cómo recorres una fila buscando 3 o más iguales seguidas?
   ¿Cómo evitas contar dos veces una corrida de 5? ¿Cómo tratas las posiciones vacías?
4. **caídaDeFichas** — por columna: ¿desde arriba o desde abajo? ¿Por qué?
5. **agregarFila(posición)** — reservar bloque nuevo, copiar, liberar el viejo. ¿En qué orden,
   para no perder datos ni dejar memoria colgada?
6. **bucleDeCascadas** — ¿cuál es exactamente la condición de parada?

---

## Hoja 5 — Partida simulada a mano

Un tablero de **4×4**. Inventa las fichas (o tíralas con un dado) y dibújalo.

Escoge una eliminación que dispare una combinación y dibuja, **paso a paso, un tablero por
paso**:

1. El tablero inicial
2. La ficha eliminada por el usuario
3. Las combinaciones detectadas (marca las fichas involucradas)
4. El tablero tras eliminar las combinaciones
5. La caída de las fichas restantes
6. Las fichas nuevas que entran arriba
7. La combinación nueva que se formó sola → **esto es una cascada**
8. Repite hasta que no aparezcan más

Al lado, lleva los contadores: eliminaciones, fichas eliminadas, combinaciones, cascadas,
puntaje.

**Esta hoja te da tres cosas:** media página del informe, la certeza de que entendiste las
cascadas antes de programarlas, y el guion exacto de la demostración del video.

Intenta también dibujar un caso donde una misma ficha esté en una combinación horizontal
**y** en una vertical al mismo tiempo. Ese es el caso que rompe las soluciones ingenuas.
