#include <iostream>
#include <fstream>
#include <string>
#include "structs.hpp"

using namespace std;



/*****
* bool tableroEnJaqueMate
******
* Esta funcion compara las posiciones posibles del rey de ton, con el tablero
* de posibles posiciones de ataque de las piezas de Sebastian, tal que:
*   1. Si la posicion actual del rey de ton esta siendo atacada
*   2. Las posiciones adyacentes del rey se encuentran atacadas.
* Entonces el rey de ton se encuentra en jaque mate.
******
* Input:
* Pieza tablero : array bidimesional de structs Pieza con simbolos chars "." y "+"
*                 tal que los char "+" simbolizan una posicion que esta siendo atacada.
*
* Pieza rey_ton: struct Pieza que simboliza al rey de ton, en tanto simbolo y posiciones
*                x, y.
* .......
******
* Returns:
* bool, Retorna un valor Verdadero si las posiciones del rey estan siendo atacados, en caso
* de encontrar una posicion no atacada, o sea un char ".", entonces el rey no se encuentra 
* en jaquemate, devolviendo el valor Falso.
*****/  

// Función tableroEnJaqueMate: Si está en jaque-mate retorna true, en caso contrario retorna false.
//bool tableroEnJaqueMate(Tablero &tablero){};
bool tableroEnJaqueMate(Pieza (&tablero)[8][8], Pieza rey_ton) {
    int reyX = rey_ton.x;
    int reyY = rey_ton.y;

    // Verificar si todas las posiciones a las que puede moverse el rey están siendo atacadas por las piezas de Sebastian
    for (int i = reyY - 1; i <= reyY + 1; ++i) {
        for (int j = reyX - 1; j <= reyX + 1; ++j) {
            // Verificar si la posición está dentro del tablero
            if (i >= 0 && i < 8 && j >= 0 && j < 8) {
                // Si la posición está vacía o es atacada por una pieza de Sebastian, sigue en jaque mate
                if (tablero[i][j].simbolo == '+' || tablero[i][j].simbolo == 'X') {
                    continue;
                } else {
                    return false; // Si la posición no está vacía ni es atacada, el rey no está en jaque mate
                }
            }
        }
    }

    // Si todas las posiciones a las que puede moverse el rey están siendo atacadas, está en jaque mate
    return true;
}





/*****
* Tablero obtenerPiezas
******
* Esta funcion es la encargada de obtener, a partir del archivo tablero.txt, un array de structs Pieza
* tal que almacene la informacion de posicion y de simbolo de cada una de las piezas de Sebastian.
******
* Input:
* const string& archivo:
* tipoParámetro NombreParámetro : Descripción Parámetro
* Pieza rey_ton: struct pieza con coordenadas x,y del rey con simbolo "X"
* .......
******
* Returns:
* Tablero, retorna un struct tablero el cual contiene un array de structs Pieza con la informacion de cada pieza 
*          de Sebastian en el tablero. Tambien, contiene un int cantidad_piezas que indica la dimension del array
*          anteriormente mencionado.
*****/  
Tablero obtenerPiezas(const string& archivo, Pieza& rey_ton){

    fstream tablero_txt;
    tablero_txt.open(archivo, ios::in);

    // Verificar apertura exitosa del archivo (Buena practica)
    if (! tablero_txt . is_open () ) {
        cout << "No se pudo abrir el archivo " << endl ;
        return Tablero();
    }

    string linea;
    int  contador = 0, num_piezas, posicion_x = 0, posicion_y = 0;
    bool primera_linea = true; 
    Tablero piezas;

    while (getline(tablero_txt, linea)){

        // Obtener cantidad de structs "Pieza", para generar struct "Tablero"
        if (primera_linea){
            
            num_piezas = stoi(linea);
            primera_linea = false;
            piezas.piezas_tablero = new Pieza[num_piezas-1];
            piezas.cantidad_piezas = num_piezas-1;
        }

        else {
            
            
            for(string::size_type i = 0; i < linea.length(); i++){ 

                if (linea[i] != '.'){

                    if (linea[i] == 'X'){
                        rey_ton.x = posicion_x;
                        rey_ton.y = posicion_y;
                    }

                    else {
                        Pieza nueva_pieza;
                        nueva_pieza.simbolo = linea[i];
                        nueva_pieza.x = posicion_x;
                        nueva_pieza.y = posicion_y;
                        piezas.piezas_tablero[contador] = nueva_pieza;
                        contador += 1;
                    }
                    
                }

                posicion_x += 1;

            }

            posicion_x = 0;
            posicion_y += 1;
        }


    }

        /*cout << "El numero de piezas de Sebastian dentro del tablero es: " << piezas.cantidad_piezas << endl;

        for (int i = 0; i < piezas.cantidad_piezas; ++i) {
            cout << "Pieza " << i + 1 << ": ";
            cout << "Símbolo: " << piezas.piezas_tablero[i].simbolo;
            cout << ", x: " << piezas.piezas_tablero[i].x;
            cout << ", y: " << piezas.piezas_tablero[i].y << endl;
        }

        cout << "\nEl rey de Ton se encuentra en: " << endl;
        cout << "x: " << rey_ton.x << endl;
        cout << "y: " << rey_ton.y << endl;*/
        
    tablero_txt.close();
    return piezas;
};



/*****
* void calcularAtaquePeon
******
* Esta funcion obtiene las coordenadas de posibles ataques de una Pieza Peon
* cambiando los simbolos "." por "+" en el tablero de analisis de posiciones de ataque.
******
* Input:
* Pieza peon: struct pieza con coordenadas x,y del peon con simbolo "P"
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analisis de posiciones de ataque.
* .......
******
* void, Tiene retorno void,ya que la funcion modifica un elemento preexistente pasado por 
*       referencia sin necesidad de retornar algo.
*****/ 
// Función para calcular y marcar las posiciones de ataque de un peón en el tablero
void calcularAtaquePeon(Pieza peon, Pieza (&tablero)[8][8]) {
    // Coordenadas del peón en el tablero acotado
    int peonX = peon.x;
    int peonY = peon.y;

    // Coordenadas de las casillas a las que el peón podría atacar hacia arriba
    int ataqueX1 = peonX - 1;
    int ataqueX2 = peonX + 1;
    int ataqueY = peonY - 1; // El peón ataca hacia arriba

    // Verificar si las casillas de ataque están dentro del tablero y marcarlas
    if (ataqueX1 >= 0 && ataqueX1 < 8 && ataqueY >= 0 && ataqueY < 8) {
        tablero[ataqueY][ataqueX1].simbolo = '+'; // Marcar la casilla de ataque con el símbolo '+'
    }

    if (ataqueX2 >= 0 && ataqueX2 < 8 && ataqueY >= 0 && ataqueY < 8) {
        tablero[ataqueY][ataqueX2].simbolo = '+'; // Marcar la casilla de ataque con el símbolo '+'
    }
}



/*****
* bool hayPiezaEnLaCasillaActual
******
* Esta funcion sirve para el analisis de piezas como la torre, alfil y reina, esto ya que si una de estas piezas llegase a 
* encontrar una pieza en el camino, la trayectoria de ataque se detendría y terminaria en donde se posiciona esta otra pieza
* en el camino. 
******
* Input:
* int x: Posicion x actual de la pieza en analisis
* int y: Posicion y actual de la pieza en analisis
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analisis de posiciones de ataque.
* Tablero piezas_sebastian: struct tablero, que contiene un array de structs piezas, que representan las piezas
*                           de sebastian con sus respectivas posiciones y simbolos.
* Pieza rey_ton: struct pieza con coodenadas x,y del rey con simbolo "X"
* .......
******
* Returns:
* bool, Retorna True si encuentra una pieza en el camino o al rey de ton, si no hay piezas en el camino y 
* el rey de ton no se encuentra, retorna False
* TipoRetorno, Descripción retorno
*****/ 
// Función para verificar si hay una pieza en la casilla actual
bool hayPiezaEnLaCasillaActual(int x, int y, Pieza (&tablero)[8][8], Tablero piezas_sebastian, Pieza rey_ton) {
    // Verificar si hay una pieza en la casilla actual en el tablero de Sebastian
    for (int i = 0; i < piezas_sebastian.cantidad_piezas; i++) {
        if (piezas_sebastian.piezas_tablero[i].x == x && piezas_sebastian.piezas_tablero[i].y == y) {
            return true; // Si hay una pieza en la casilla actual en el tablero de Sebastian, detener el ataque en esta dirección
        }
    }

    // Verificar si la casilla actual es ocupada por el rey de Ton
    if (x == rey_ton.x && y == rey_ton.y) {
        return true; // Si es el rey de Ton, detener el ataque en esta dirección
    }
    
    return false; // No hay pieza en la casilla actual ni es el rey de Ton
}



/*****
* void calcularAtaqueTorre
******
* Esta funcion obtiene las coordenadas de posibles ataques de una Pieza Torre
* cambiando los simbolos "." por "+" en el tablero de analisis de posiciones de ataque.
******
* Input:
* Pieza torre: struct pieza con coordenadas x,y de la torre con simbolo "T"
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analisis de posiciones de ataque.
* Tablero piezas_sebastian: struct tablero, que contiene un array de structs piezas, que representan las piezas
*                           de sebastian con sus respectivas posiciones y simbolos.
* Pieza rey_ton: struct pieza con coordenadas x,y del rey con simbolo "X"
* .......
******
* void, Tiene retorno void,ya que la funcion modifica un elemento preexistente pasado por 
*       referencia sin necesidad de retornar algo.
*****/ 
// Función para calcular y marcar las posiciones de ataque de una torre en el tablero
void calcularAtaqueTorre(Pieza torre, Pieza (&tablero)[8][8], Tablero piezas_sebastian, Pieza rey_ton) {
    int torreX = torre.x;
    int torreY = torre.y;

    // Verificar posiciones hacia arriba
    for (int i = torreY - 1; i >= 0; i--) {
        if (hayPiezaEnLaCasillaActual(torreX, i, tablero, piezas_sebastian, rey_ton)) {
            tablero[i][torreX].simbolo = '+';
            break; // Si hay una pieza en la casilla actual, detener el ataque en esta dirección
        }
        tablero[i][torreX].simbolo = '+';
    }

    // Verificar posiciones hacia abajo
    for (int i = torreY + 1; i < 8; i++) {
        if (hayPiezaEnLaCasillaActual(torreX, i, tablero, piezas_sebastian, rey_ton)) {
            tablero[i][torreX].simbolo = '+';
            break; // Si hay una pieza en la casilla actual, detener el ataque en esta dirección
        }
        tablero[i][torreX].simbolo = '+';
    }

    // Verificar posiciones hacia la izquierda
    for (int j = torreX - 1; j >= 0; j--) {
        if (hayPiezaEnLaCasillaActual(j, torreY, tablero, piezas_sebastian, rey_ton)) {
            tablero[torreY][j].simbolo = '+';
            break; // Si hay una pieza en la casilla actual, detener el ataque en esta dirección
        }
        tablero[torreY][j].simbolo = '+';
    }

    // Verificar posiciones hacia la derecha
    for (int j = torreX + 1; j < 8; j++) {
        if (hayPiezaEnLaCasillaActual(j, torreY, tablero, piezas_sebastian, rey_ton)) {
            tablero[torreY][j].simbolo = '+';
            break; // Si hay una pieza en la casilla actual, detener el ataque en esta dirección
        }
        tablero[torreY][j].simbolo = '+';
    }
}



/*****
* void calcularAtaqueAlfil
******
* Esta funcion obtiene las coordenadas de posibles ataques de una Pieza Alfil
* cambiando los simbolos "." por "+" en el tablero de analisis de posiciones de ataque.
******
* Input:
* Pieza alfil: struct pieza con coordenadas x,y del alfil con simbolo "A"
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analisis de posiciones de ataque.
* Tablero piezas_sebastian: struct tablero, que contiene un array de structs piezas, que representan las piezas
*                           de sebastian con sus respectivas posiciones y simbolos.
* Pieza rey_ton: struct pieza con coordenadas x,y del rey con simbolo "X"
* .......
******
* void, Tiene retorno void,ya que la funcion modifica un elemento preexistente pasado por 
*       referencia sin necesidad de retornar algo.
*****/ 
// Función para calcular y marcar las posiciones de ataque de un alfil en el tablero
void calcularAtaqueAlfil(Pieza alfil, Pieza (&tablero)[8][8], Tablero piezas_sebastian, Pieza rey_ton) {
    int alfilX = alfil.x;
    int alfilY = alfil.y;

    // Verificar posiciones en la diagonal superior izquierda
    for (int i = 1; alfilX - i >= 0 && alfilY - i >= 0; i++) {
        if (hayPiezaEnLaCasillaActual(alfilX - i, alfilY - i, tablero, piezas_sebastian, rey_ton)) {
            tablero[alfilY - i][alfilX - i].simbolo = '+'; // Pintar la casilla incluso si hay una pieza
            break; // Detener el movimiento en esta dirección
        }
        tablero[alfilY - i][alfilX - i].simbolo = '+';
    }

    // Verificar posiciones en la diagonal superior derecha
    for (int i = 1; alfilX + i < 8 && alfilY - i >= 0; i++) {
        if (hayPiezaEnLaCasillaActual(alfilX + i, alfilY - i, tablero, piezas_sebastian, rey_ton)) {
            tablero[alfilY - i][alfilX + i].simbolo = '+'; // Pintar la casilla incluso si hay una pieza
            break; // Detener el movimiento en esta dirección
        }
        tablero[alfilY - i][alfilX + i].simbolo = '+';
    }

    // Verificar posiciones en la diagonal inferior izquierda
    for (int i = 1; alfilX - i >= 0 && alfilY + i < 8; i++) {
        if (hayPiezaEnLaCasillaActual(alfilX - i, alfilY + i, tablero, piezas_sebastian, rey_ton)) {
            tablero[alfilY + i][alfilX - i].simbolo = '+'; // Pintar la casilla incluso si hay una pieza
            break; // Detener el movimiento en esta dirección
        }
        tablero[alfilY + i][alfilX - i].simbolo = '+';
    }

    // Verificar posiciones en la diagonal inferior derecha
    for (int i = 1; alfilX + i < 8 && alfilY + i < 8; i++) {
        if (hayPiezaEnLaCasillaActual(alfilX + i, alfilY + i, tablero, piezas_sebastian, rey_ton)) {
            tablero[alfilY + i][alfilX + i].simbolo = '+'; // Pintar la casilla incluso si hay una pieza
            break; // Detener el movimiento en esta dirección
        }
        tablero[alfilY + i][alfilX + i].simbolo = '+';
    }
}



/*****
* void calcularAtaqueRey
******
* Esta funcion obtiene las coordenadas de posibles ataques de una Pieza Rey
* cambiando los simbolos "." por "+" en el tablero de analisis de posiciones de ataque.
******
* Input:
* Pieza rey: struct pieza con coordenadas x,y del rey con simbolo "K"
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analisis de posiciones de ataque.
* .......
******
* void, Tiene retorno void,ya que la funcion modifica un elemento preexistente pasado por 
*       referencia sin necesidad de retornar algo.
*****/ 
// Función para calcular y marcar las posiciones de ataque de un rey en el tablero
void calcularAtaqueRey(Pieza rey, Pieza (&tablero)[8][8]) {
    int movimientos[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int reyX = rey.x;
    int reyY = rey.y;

    for (int i = 0; i < 8; i++) {
        int nx = reyX + movimientos[i][0];
        int ny = reyY + movimientos[i][1];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
            if (tablero[ny][nx].simbolo == '.' || tablero[ny][nx].simbolo != rey.simbolo) {
                tablero[ny][nx].simbolo = '+';
            }
        }
    }
}



/*****
* void calcularAtaqueReina
******
* Esta funcion obtiene las coordenadas de posibles ataques de una Pieza Reina
* cambiando los simbolos "." por "+" en el tablero de analisis de posiciones de ataque.
******
* Input:
* Pieza reina: struct pieza con coordenadas x,y de la reina con simbolo "R"
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analis* de posiciones de ataque.
* Tablero piezas_sebastian: struct tablero, que contiene un array de structs piezas, que representan las piezas
*                           de sebastian con sus respectivas posiciones y simbolos.
* Pieza rey_ton: struct pieza con coordenadas x,y del rey con simbolo "X"
* .......
******
* void, Tiene retorno void,ya que la funcion modifica un elemento preexistente pasado por 
*       referencia sin necesidad de retornar algo.
*****/ 
// Función para calcular y marcar las posiciones de ataque de una reina en el tablero
void calcularAtaqueReina(Pieza reina, Pieza (&tablero)[8][8], Tablero piezas_sebastian, Pieza rey_ton) {
    // Calcular los movimientos de la reina como una combinación de los movimientos de una torre y un alfil
    calcularAtaqueTorre(reina, tablero, piezas_sebastian, rey_ton);
    calcularAtaqueAlfil(reina, tablero, piezas_sebastian, rey_ton);
}



/*****
* void calcularAtaqueCaballo
******
* Esta funcion está encargada de marcar las posibles coordenadas de ataque de la pieza 
* Caballo de Sebastian.
******
* Input:
* Pieza caballo : Struct pieza con informacion de posicion x, y en coordenadas de array
* Pieza tablero : Tablero simulado que contiene las posibles posiciones de ataque de 
*                 las piezas de Sebastian (marcadas con char "+") y las que no 
*                 ("marcadas con char ".)
* .......
******
* Returns:
* void, Tiene retorno void,ya que la funcion modifica un elemento preexistente pasado por 
*       referencia sin necesidad de retornar algo.
*****/ 
// Función para calcular y marcar las posiciones de ataque de un caballo en el tablero
void calcularAtaqueCaballo(Pieza caballo, Pieza (&tablero)[8][8]) {
    int movimientos[8][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};
    int caballoX = caballo.x;
    int caballoY = caballo.y;

    for (int i = 0; i < 8; i++) {
        int nx = caballoX + movimientos[i][0];
        int ny = caballoY + movimientos[i][1];
        if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
            if (tablero[ny][nx].simbolo == '.' || tablero[ny][nx].simbolo != caballo.simbolo) {
                tablero[ny][nx].simbolo = '+';
            }
        }
    }
}



/*****
* void analizarCasillasTablero
******
* Esta funcion se encarga de rellenar el tablero vacio (array bidimensional  de 
* structs Pieza con simbolos ".") con chars "+" que representan posiciones de ataque 
* de las piezas de Sebastian.
******
* Input:
* Pieza rey_ton : struct pieza con coordenadas x,y del rey con simbolo "X"
* Pieza tablero: array bidimensional de structs pieza, su uso sirve para el analis* de posiciones de ataque.
* Tablero piezas_sebastian: struct tablero, que contiene un array de structs piezas, que representan las piezas
*                           de sebastian con sus respectivas posiciones y simbolos.
* .......
******
* Returns:
* void, esta funcion no retorna nada, ya que su proposito es modificar el arrary de structs
* Pieza nombrado tablero, cambiando para las posciones posibles de ataque de las piezas de
* Sebastias sus simbolos de "." por "+". 
*****/  
void analizarCasillasTablero(Pieza rey_ton, Pieza (&tablero)[8][8], Tablero piezas_sebastian) {
    for (int i = 0; i < piezas_sebastian.cantidad_piezas; i++) {
    

        switch (piezas_sebastian.piezas_tablero[i].simbolo) {
            case 'P':
                calcularAtaquePeon(piezas_sebastian.piezas_tablero[i], tablero);
                break;
            case 'T':
                calcularAtaqueTorre(piezas_sebastian.piezas_tablero[i], tablero, piezas_sebastian, rey_ton);
                break;
            case 'A':
                calcularAtaqueAlfil(piezas_sebastian.piezas_tablero[i], tablero,  piezas_sebastian, rey_ton);
                break;
            case 'K':
                calcularAtaqueRey(piezas_sebastian.piezas_tablero[i],  tablero);
                break;
            case 'R':
                calcularAtaqueReina(piezas_sebastian.piezas_tablero[i], tablero, piezas_sebastian, rey_ton);
                break;
            case 'C':
                calcularAtaqueCaballo(piezas_sebastian.piezas_tablero[i],tablero);
                break;
            default:
                // No hacer nada si no es una pieza válida
                break;
        }


    }
}