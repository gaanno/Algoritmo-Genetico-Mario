// compilacion y ejecucion
// g++ main.cpp -o main && ./main

#include <iostream>
#include <string>
#include <vector>
#include "Mundo.h"
#include <cstdlib>
#include <ctime>
using namespace std;

void imprimirVector(vector<char> vector);
int main()
{
    srand(time(NULL));
    string nombreArchivo = "./archivos/ag2o.txt";
    Mundo mundo(nombreArchivo);
    vector<vector<char>> solucionesParciales;
    vector<vector<char>> solucionesValidas;
    vector<char> solucionArtificial;


    int numeroSolucionesParciales = 100000;
    int indice;
    int largoSolucion = 2*mundo.largoMundo;

    // rellena con soluciones parciales
    for (indice = 0; indice < numeroSolucionesParciales; indice++)
    {
        vector<char> solucionParcial = mundo.poblacionInicial(largoSolucion);
        solucionesParciales.push_back(solucionParcial);
    }


    // verifica si las soluciones parciales son validas
    for (indice = 0; indice < solucionesParciales.size(); indice++)
    {
        vector<char> sol = mundo.comprobarSolucion(solucionesParciales[indice]);
        if (sol.size() > 0)
        {
            solucionesValidas.push_back(sol);
        }
    }

    for (indice = 0; indice < solucionesValidas.size(); indice++)
    {
        imprimirVector(solucionesValidas[indice]);
    }
//    cout << "Numero soluciones validas: " << solucionesValidas.size() << endl;
    // imprime las soluciones validas verificadas

    // movimiento.getEstadoMario();
    return 0;
}

void imprimirVector(vector<char> vector)
{
    for (int indice = 0; indice < vector.size(); indice++)
    {
        cout << vector[indice] << " ";
    }
    cout << endl << endl;
}