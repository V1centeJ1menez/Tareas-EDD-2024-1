#pragma once

// Registro Pieza: Definirá los datos básicos para identificar una pieza
struct Pieza {
 char simbolo; // Define qué tipo de pieza es y su caracter
 int x, y; // Su posición dentro del tablero [0, 7] x [0, 7]
};

// Estructura Tablero: Define un tablero con un arreglo de “Piezas”
struct Tablero {
 Pieza* piezas_tablero; // Lista de piezas que tiene el tablero
 int cantidad_piezas = -1;
};
