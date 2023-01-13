// compilacion y ejecucion
// g++ main.cpp -o main && ./main

#include <iostream>
#include <string>
#include "Archivo.h"

using namespace std;

int main()
{
    // nombre del archivo que contiene el mapa
    string nombreArchivo = "ag1.txt";

    // crea el objeto archivo
    Archivo archivo(nombreArchivo);

    // hago lo demas...
    archivo.abrirArchivo();
    cout << "Largo: " << archivo.largo << endl;
    cout << "Ancho: " << archivo.ancho << endl;
    archivo.imprimirMapa();
    return 0;
}