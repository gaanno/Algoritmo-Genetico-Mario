// compilacion y ejecucion
// g++ main.cpp -o main && ./main

#include <iostream>
#include <string>
#include "Archivo.h"
#include "Movimiento.h"

using namespace std;

int main()
{
    // nombre del archivo que contiene el mapa
    string nombreArchivo = "./archivos/ag2.txt";

    // crea objetos
    Archivo archivo(nombreArchivo);
    Movimiento movimiento;

    // Lee el archivo y crea el mapa
    archivo.abrirArchivo();

    // setea la posicion inicial
    movimiento.setPosicionActual(archivo.posicionInicial[0], archivo.posicionInicial[1]);

    cout << "Largo: " << archivo.largo << endl;
    cout << "Ancho: " << archivo.ancho << endl;
    archivo.imprimirMapa();
    return 0;
}