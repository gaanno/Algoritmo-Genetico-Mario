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
    mundo.abrirMundo();
    //mundo.imprimirMapa();

    
    //mundo.moverDerecha();
    mundo.moverDerecha();

    //mundo.moverIzquierda();
    mundo.moverSaltoAlto();
    mundo.moverDerecha();
    mundo.moverDerecha();

    //mundo.getEstadoMario();
    //mundo.moverSaltolargo();
    mundo.getMovimientosMario();
   mundo.imprimirMapa();


    // movimiento.getEstadoMario();
    return 0;
}