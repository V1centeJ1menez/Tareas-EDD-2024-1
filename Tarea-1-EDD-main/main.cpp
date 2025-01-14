#include <iostream>
#include <fstream>
#include <string>
#include "functions.cpp"
#include "structs.hpp"

using namespace std;

/*****
* int Main
******
* Funcion principal del programa, encargada de hacer llamadas
* a funciones principales, logrando el proposito general del programa
******
* Input:
*
* .......
******
* Returns:
* int, retorna 0 cuando el programa termina su ejecucion, liberando la memoria
* asignada al programa y dandole fin a este mismo.
*****/


int main(){

    // Definir pieza del rey
    Pieza rey_ton;
    rey_ton.simbolo = 'X';

    // Apertura de archivo tablero ascii
    string archivo_tablero = "tableros/tablero2.txt";

    // Llamada a funcion que genera el struct Tablero con la lista de piezas 
    // de sebastian dentro del tablero
    Tablero lista_piezas = obtenerPiezas(archivo_tablero, rey_ton);


    // Segmento de codigo que rescata un error de apertura del archivo
    // ya que en el caso de abrirse mal, inicia un struct tablero vacio, con 
    // el valor de cantidad_piezas en -1.    
    if (lista_piezas.cantidad_piezas == -1){
        cout << "Hubo un error al obtener el tablero desde el archivo." << endl;
        return 0;
    } 

    // Se genera un array bidimensional que simula un tablero vacio
    Pieza tablero[8][8];  

     // Llenar el tablero con valores por defecto
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tablero[i][j].simbolo = '.'; // Simbolo de casilla vacia
            tablero[i][j].x = j; // Coordenada x es la columna
            tablero[i][j].y = i; // Coordenada y es la fila, invertida
        }
    }

    // Se hace llamada a funcion que rellena el tablero iniciado anteriormente 
    // con chars "+" que simulan las posibles posiciones de ataque de cada pieza
    // de sebastian en el tablero.
    analizarCasillasTablero(rey_ton, tablero, lista_piezas);


    // Imprimir el contenido del tablero
    /*for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << tablero[i][j].simbolo << " ";
        }
    cout << endl; // Nueva línea al final de cada fila
    }*/

    // Con el tablero relleno, se llama a la funcion que compara la posicion del rey 
    // de ton y sus posibles movimiento adyacentes con el tablero relleno. La cual define
    // si el rey de ton se encuentra o no en jaque mate.
    bool jaque_mate = tableroEnJaqueMate(tablero, rey_ton);

    //Imprimir mensaje indicando si el rey de Ton está en jaque mate o no
    if (jaque_mate) {
        //cout << "El rey de Ton está en jaque mate." << endl;
        cout << "Si." << endl;
    } else {
        //cout << "El rey de Ton no está en jaque mate." << endl;
        cout << "No."<< endl;
    }



    return 0;
}