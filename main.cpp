// compilacion y ejecucion
// g++ main.cpp -o main && ./main

#include <iostream>
#include <string>
#include "Mundo.h"

using namespace std;

int main()
{
    // nombre del archivo que contiene el mapa
    // al terminar hay que cambiarlo por world.txt
    string nombreArchivo = "./archivos/ag2.txt";

    // crea objetos
    Mundo mundo(nombreArchivo);

    // mundo.moverDerecha();
    cout << "------------ Mapa inicial ------------" << endl;
    mundo.abrirMundo();
    mundo.imprimirMapa();

    cout << "------------ Mapa luego de mover a la derecha ------------" << endl;
    mundo.moverDerecha();
    mundo.getEstadoMario();
    mundo.imprimirMapa();


    // movimiento.getEstadoMario();
    return 0;
}