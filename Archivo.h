/*
    Archivo encargado de leer el mapa en formato txt
    @author Gabo
*/

#include <iostream>
#include <string>  // nombre archivo
#include <fstream> // leer archivo
#include <sstream> // convertir string a int

using namespace std;

// clase para manipular el mapa
class Archivo
{
public:
    std::string nombreArchivo;
    int largo;
    int ancho;
    int **mapa;
    int posicionInicial[2];
    void abrirArchivo();
    void imprimirMapa();
    void crearMapa();
    void actualizarMapa(int **nuevoMapa);
    Archivo(std::string nombreArchivo);
};

// constructor
Archivo::Archivo(std::string nombreArchivo)
{
    this->nombreArchivo = nombreArchivo;
}

void Archivo::abrirArchivo()
{
    // abre el archivo
    ifstream archivo(nombreArchivo);
    string linea;
    int numeroLinea = 0;

    // si no pudo abrir el archivo finaliza el programa
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    // lee el archivo y muestra el numero de linea
    while (getline(archivo, linea))
    {
        if (numeroLinea == 0)
        {
            largo = stoi(linea);
        }
        else if (numeroLinea == 1)
        {
            ancho = stoi(linea);
            crearMapa();
        }
        else
        {
            // convierte la linea a stringstream para convertirla a numeros
            stringstream ss(linea);
            int numero;
            int contador = 0;

            while (ss >> numero)
            {
                // posicion de inicio
                if (numero == 3)
                {
                    posicionInicial[0] = numeroLinea - 2;
                    posicionInicial[1] = contador;
                }

                mapa[numeroLinea - 2][contador] = numero;
                contador++;
            }
        }
        numeroLinea++;
    }
}

// crea el mapa
void Archivo::crearMapa()
{
    mapa = new int *[ancho];
    for (int i = 0; i < ancho; i++)
    {
        mapa[i] = new int[largo];
    }
}

// imprime el mapa
void Archivo::imprimirMapa()
{
    for (int i = 0; i < ancho; i++)
    {
        for (int j = 0; j < largo; j++)
        {
            cout << mapa[i][j] << ' ';
        }
        cout << endl;
    }
}

void Archivo::actualizarMapa(int **nuevoMapa)
{
    mapa = nuevoMapa;
}