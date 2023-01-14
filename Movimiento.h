#include <iostream>

using namespace std;

class Movimiento
{
public:
    int derecha(int **mapa);
    int izquierda(int **mapa);
    int saltoAlto(int **mapa);
    int saltoLargo(int **mapa);
    void setPosicionActual(int x, int y); // fila, columna
    void getPosicionActual();

private:
    int posicionActual[2]; // x,y
};

// Movimiento derecha: +1 en eje x de un arreglo de 2 dimensiones
int Movimiento::derecha(int **mapa)
{
    cout << mapa[0][0] << endl;
    return **mapa;
}

// Setea la posicion actual
void Movimiento::setPosicionActual(int x, int y)
{
    posicionActual[0] = x;
    posicionActual[1] = y;
}

void Movimiento::getPosicionActual()
{
    cout << "Fila: " <<  this->posicionActual[0] << endl;
    cout << "Columna: " <<  this->posicionActual[1] << endl;
}