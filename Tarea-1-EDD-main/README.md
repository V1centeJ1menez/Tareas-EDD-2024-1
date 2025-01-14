# Consideraciones previas a la ejecucion

- Las piezas de sebastian son vistas desde abajo hacia arriba, lo que es importante para la implementacion de la funcion ```calcularAtaquePeon()```

- Se utilizan coordenadas cartesianas para entender los arrays bidimensionales (7,0) x (0,7).

- Para la lectura de los tableros utilizar la instrucción de la funcion main() ``` string archivo_tablero = "tableros/tablero{caso_tablero}.txt" ``` dentro del archivo   main.cpp. Tener en cuenta que el directorio posee 6 tableros de prueba, en el caso de querer analizar otro tablero, agregarlo al directorio y cambiar la instrucción anterior tal que ``` string archivo_tablero = "tableros/{nombre_del_archivo_que_contiene_el_tablero}.txt" ```


Compilar de la siguiente forma:
    
    g++ main.cpp -o main -Wall. 

Ejecutar con:

    ./main


# Abstracción de la tarea - Flujo del programa

La idea era imaginar las posiciones posibles de ataque de las piezas de Sebastian dentro del tablero entregado y luego ver a partir de estas, como afectaba la posicion del rey de Ton y sus posibilidades de movimientos adyacentes. Tal que:
 
 (I). si la posicion del rey de Ton está atacado  

 (II). Las posiciones adyancentes del rey de Ton están atacadas.

Entonces el rey se encuentra en jaque-mate.

---
Una de las primeras tareas era mapear todas las piezas de tablero.txt, tal que se pudiera obtener una lista de Piezas de Sebastian y el Rey de Ton de forma individual como un struct piezas para un posterior analisis.

1) Implementar funcion ```obtenerPiezas()```

Ya con las piezas mapeadas, queda hacer el analisis de posibles movimiento de ataque de las piezas de Sebastian, para esto se hace lo siguiente:

- Generar un array bidimensional que simule un tablero 8x8, con elementos Pieza de simbolo "."

Con el tablero generado seguía:

2) Implementar funcion ```analizarCasillaTablero()```

Funcion que se encarga de iterar la lista de piezas de Sebastian y segun la pieza que el ciclo reciba, obtener las posiciones de posibles ataques segun su simbolo y posicion actual. Para esto:

3) Implementar funcion ```calcularAtaquesPeon()```
4) Implementar funcion ```calcularAtaquesCaballo()```
5) Implementar funcion ```calcularAtaquesRey()```
6) Implementar funcion ```calcularAtaquesTorre()```
7) Implementar funcion ```calcularAtaquesAlfil()```
8) Implementar funcion ```calcularAtaquesReina()```

A partir de las observaciones de cada uno de los movimientos de las piezas, se notó que para la torre, alfil y la reina(torre+alfil), ocurre que cuando se analiza una trayectoria posible de ataque de estas piezas, estas pueden encontrarse con otras en el camino, lo que interrumpe de alguna forma su trayectoria. Para esto:

9) Implementar funcion ```hayPiezaEnLaCasillaActual()```

Esta funcion permite dar cuenta de que en el caso de que una trayectoria posible de ataque para una de las piezas mencionadas se vea interrumpida por una pieza en el camino, entonces pintara la posicion de la pieza en el camino (esto porque la pieza se encontraría "protegida", en este caso ya que solo encontraria piezas aliadas) y termine de analizar dicha trayectoria.

Por ejemplo:

```tablero.txt ```
    3
|   |   |   |   |   |   |   |   |
|---|---|---|---|---|---|---|---|
| . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . |
| . | . | . | . | . | . | . | . |
| T | . | . | . | . | . | . | . |
| T | . | . | . | . | . | . | X |

Analizado quedaria:

```Pieza analizarCasillasTablero(rey_ton, tablero, lista_piezas);```
|   |   |   |   |   |   |   |   |
|---|---|---|---|---|---|---|---|
| + | . | . | . | . | . | . | . |
| + | . | . | . | . | . | . | . |
| + | . | . | . | . | . | . | . |
| + | . | . | . | . | . | . | . |
| + | . | . | . | . | . | . | . |
| + | . | . | . | . | . | . | . |
| + | + | + | + | + | + | + | + |
| + | + | + | + | + | + | + | + |


Con el tablero ya analizado y las posiciones de ataque posibles rellenas, ahora se procede a estudiar la posicion del rey y sus posibles movimiento respecto al tablero en el que se encuentra. Para esto:

10) Implementar funcion ```tableroEnJaqueMate()```

Finalmente se consuta por cada posicion posible del rey, si está siendo atacada por una pieza de sebastian, esto a partir de consultar las mismas coordenadas del tablero previamente analizado y encontrar char "." (no atacada) o "+" (atacada). Tal que si (I) y (II) se cumplen, entonces el rey de Ton se encuentra en jaque-mate.
