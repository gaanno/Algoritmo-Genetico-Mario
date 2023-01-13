#include <iostream>
#include <string>
#include "Archivo.h"

using namespace std;

int main()
{
    string nombreArchivo = "ag1.txt";
    Archivo archivo(nombreArchivo);
    archivo.abrirArchivo();
    cout << "Largo: " << archivo.largo << endl;
    cout << "Ancho: " << archivo.ancho << endl;
    archivo.imprimirMapa();
    return 0;
}