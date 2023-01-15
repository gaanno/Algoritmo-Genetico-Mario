// compilacion y ejecucion
// g++ main.cpp -o main && ./main

#include <iostream>
#include <string>
#include <vector>
#include "Mundo.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

double uniformRate = 0.2;
double mutationRate = 0.2;
double crossRate = 0.4;
int tournamentSize = 5;
bool elitism = true;


void imprimirVector(vector<char> vector);
vector<vector<char>> evolvePopulation(vector<vector<char>> poblacion);
vector<vector<char>> geneticAlgorithm(vector<vector<char>> poblacionInicial);
vector<char> crossover(vector<char> padre1, vector<char> padre2);
vector<char> tournamentSelection(vector<vector<char>> poblacion);
void mutate(vector<char> hijo);
double fitness(vector<char> solucion);
bool comparar(vector<char> solucion1, vector<char> solucion2);


int main()
{
    srand(time(NULL));
    string nombreArchivo = "./world.txt";
    Mundo mundo(nombreArchivo);
    vector<vector<char>> solucionesParciales;
    vector<vector<char>> poblacionInicial;

    // genera soluciones parciales
    int numeroSolucionesParciales = 10000;

    // largo de la solucion sometida al azar
    int largoSolucion = mundo.largoMundo;
    int indice;

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
            poblacionInicial.push_back(sol);
        }
    }

    /**
        for (indice = 0; indice < poblacionInicial.size(); indice++)
        {
            imprimirVector(poblacionInicial[indice]);
        }
        */
    cout << "Numero soluciones validas: " << poblacionInicial.size() << endl;

    // realiza el algoritmo utilizando la solucion parcial
    vector<vector<char>> poblacionFinal = geneticAlgorithm(poblacionInicial);
    

    return 0;
}
void imprimirVector(vector<char> vector)
{
    for (int i = 0; i < vector.size(); i++)
    {
        cout << vector[i];
    }
    cout << endl;
}

// realiza el algoritmo genetico
//population
vector<vector<char>> geneticAlgorithm(vector<vector<char>> poblacionInicial)
{
    vector<vector<char>> poblacion = poblacionInicial;
    int indice;

    // realiza el algoritmo genetico
    while (true)
    {
        // ordena la poblacion
        sort(poblacion.begin(), poblacion.end(), comparar);

        // imprime la mejor solucion
        // imprime la mejor solucion
        // queda en un bucle infinito ,,,, 
        // tenemos que ver como lo sacamos si sobra tiempo
        // pero si no parece que esta es la solucion
        //
        cout << "Mejor solucion: ";
        imprimirVector(poblacion[0]);

        // realiza la evolucion de la poblacion
         
         poblacion = evolvePopulation(poblacion);
    }

    return poblacion;
}


// realiza la seleccion de la poblacion
vector<vector<char>> evolvePopulation(vector<vector<char>> poblacion)
{
    vector<vector<char>> nuevaPoblacion;
    int indice;

    // agrega la mejor solucion
    if (elitism)
    {
        nuevaPoblacion.push_back(poblacion[0]);
    }

    // realiza el cruce
    for (indice = 0; indice < poblacion.size(); indice++)
    {
        vector<char> padre1 = tournamentSelection(poblacion);
        vector<char> padre2 = tournamentSelection(poblacion);
        vector<char> hijo = crossover(padre1, padre2);
        nuevaPoblacion.push_back(hijo);
    }

    // realiza la mutacion
    for (indice = 0; indice < nuevaPoblacion.size(); indice++)
    {
        mutate(nuevaPoblacion[indice]);
    }
    return nuevaPoblacion;
}

// realiza el cruce
vector<char> crossover(vector<char> padre1, vector<char> padre2)
{
    vector<char> hijo;
    int indice;

    // realiza el cruce
    if (rand() <= crossRate)
    {
        // realiza el cruce
        for (indice = 0; indice < padre1.size(); indice++)
        {
            if (rand() <= 0.5)
            {
                hijo.push_back(padre1[indice]);
            }
            else
            {
                hijo.push_back(padre2[indice]);
            }
        }
    }
    else
    {
        // no realiza el cruce
        for (indice = 0; indice < padre1.size(); indice++)
        {
            hijo.push_back(padre1[indice]);
        }
    }

    return hijo;
}

// realiza la mutacion
void mutate(vector<char> hijo)
{
    int indice;

    // realiza la mutacion
    for (indice = 0; indice < hijo.size(); indice++)
    {
        if (rand() <= mutationRate)
        {
            if (hijo[indice] == '0')
            {
                hijo[indice] = '1';
            }
            else
            {
                hijo[indice] = '0';
            }
        }
    }
}

// realiza la seleccion por torneo
vector<char> tournamentSelection(vector<vector<char>> poblacion)
{
    vector<vector<char>> torneo;
    int indice;

    // realiza la seleccion por torneo
    for (indice = 0; indice < tournamentSize; indice++)
    {
        int indiceAleatorio = rand() % poblacion.size();
        torneo.push_back(poblacion[indiceAleatorio]);
    }

    // ordena el torneo
    sort(torneo.begin(), torneo.end(), comparar);

    return torneo[0];
}

// evalua la solucion
double fitness(vector<char> solucion)
{
    int fitness2 = 0;
    int indice;

    // evalua la solucion
    for (indice = 0; indice < solucion.size(); indice++)
    {
        if (solucion[indice] == '1')
        {
            fitness2++;
        }
    }

    return fitness2;
}

// compara dos soluciones
bool comparar(vector<char> solucion1, vector<char> solucion2)
{
    return solucion1[solucion1.size() - 1] > solucion2[solucion2.size() - 1];
}





