# Bitácora

Aquí voy anotando los problemas que salieron y cómo los arreglé.

- Las fichas que quedan partidas entre dos bytes: toca leer el pedazo de cada byte y juntarlos.
- Una ficha que está en una combinación horizontal y vertical a la vez: primero se marcan
  todas en un mapa de bits y al final se eliminan, así no se cuenta dos veces.
- Pendiente: hay combinaciones horizontales que no se están eliminando.
