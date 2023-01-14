/*
    Mundo encargado de leer el mapa en formato txt
    @author Gabo
*/

/* reglas del movimiento
0 representa casilla libre: Mario puede avanzar a esa casilla.
1 representa casilla impenetrable: Mario no puede avanzar a esa casilla.
2 representa enemigo: Mario muere si avanza a esa casilla (excepto por arriba).
3 representa la posición de Mario para comenzar (única, debe estar en coordenada 0 de x).
*/

#include <iostream>
#include <string>  // nombre mundo
#include <fstream> // leer mundo
#include <sstream> // convertir string a int
#include <vector>

using namespace std;

/**
 * Clase encargada de manejar el mundo
 */
class Mundo
{
public:
    // constructor
    Mundo(string nombreMundo);

    // relacionado con el mundo
    void abrirMundo();
    void crearMapa();
    void imprimirMapa();

    // relacionado con el movimiento
    void moverDerecha();
    void moverIzquierda();
    void moverArriba();
    void moverAbajo();

    // relacionado con mario
    void getPosicionActual();
    void getEstadoMario();

private:
    // relacionado con el mundo
    string nombreMundo;
    int largoMundo;
    int anchoMundo;
    int **mapa = nullptr;

    // relacionado con mario
    int posicionActual[2];
    string estadoMario = "vivo";
    void actualizarPosicionMario(int fila, int columna);
    void setEstadoMario(string estado);

    // relacionado con el movimiento
    bool checkeoMovimientoValido(char movimiento);
    void checkeoGravedad();
    void checkeoColisiones();
    void comprobacionInicialMario();
};

/**
 * Constructor de la clase
 */
Mundo::Mundo(string nombreMundo)
{
    this->nombreMundo = nombreMundo;
}

/**
 * Abre el mundo y lo carga en memoria
 */
void Mundo::abrirMundo()
{
    // abre el mundo
    ifstream mundo(nombreMundo);
    string linea;
    int numeroLinea = 0;

    // si no pudo abrir el mundo finaliza el programa
    if (!mundo.is_open())
    {
        cout << "No se pudo abrir el mundo" << endl;
        exit(1);
    }

    // lee el mundo y muestra el numero de linea
    while (getline(mundo, linea))
    {
        if (numeroLinea == 0)
        {
            largoMundo = stoi(linea);
        }
        else if (numeroLinea == 1)
        {
            anchoMundo = stoi(linea);
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
                    posicionActual[0] = numeroLinea - 2;
                    posicionActual[1] = contador;
                }

                mapa[numeroLinea - 2][contador] = numero;
                contador++;
            }
        }
        numeroLinea++;
    }
    // una vez terminado de cargar el mapa verifico si mario esta volando
    comprobacionInicialMario();
}

// crea el mapa
void Mundo::crearMapa()
{
    mapa = new int *[anchoMundo];
    for (int i = 0; i < anchoMundo; i++)
    {
        mapa[i] = new int[largoMundo];
    }
}

/**
 * Imprime el mapa
 */
void Mundo::imprimirMapa()
{
    for (int i = 0; i < anchoMundo; i++)
    {
        for (int j = 0; j < largoMundo; j++)
        {
            cout << mapa[i][j] << ' ';
        }
        cout << endl;
    }
}

/**
 * Realiza un movimiento hacia la derecha
 */
void Mundo::moverDerecha()
{
    if (checkeoMovimientoValido('d'))
    {
        int fila = posicionActual[0];
        int columna = posicionActual[1] + 1;
        actualizarPosicionMario(fila, columna);
    }
}

/**
 * Verifica si el movimiento  a realizar es valido
 * @param movimiento es el tipo de movimiento a realizar
 * @return true si el movimiento es valido, false si no lo es
 */
bool Mundo::checkeoMovimientoValido(char movimiento)
{
    switch (movimiento)
    {
    case 'd':
        cout << "bloque derecha: " << mapa[posicionActual[0]][posicionActual[1] + 1] << endl;
        if (mapa[posicionActual[0]][posicionActual[1] + 1] != 1)
        {
            return true;
        }
        break;
    }
    return false;
}

/**
 * Obtiene la posicion de mario
 */
void Mundo::getPosicionActual()
{
    cout << "Posicion actual: " << posicionActual[0] << " " << posicionActual[1] << endl;
}

/**
 * Actualiza la posicion de mario en el mapa
 */
void Mundo::actualizarPosicionMario(int fila, int columna)
{
    mapa[posicionActual[0]][posicionActual[1]] = 0;
    posicionActual[0] = fila;
    posicionActual[1] = columna;
    mapa[fila][columna] = 3;
    checkeoColisiones();
}

/**
 * Comprueba si mario esta volando
 */
void Mundo::checkeoGravedad()
{
    if (mapa[posicionActual[0] + 1][posicionActual[1]] == 0)
    {
        actualizarPosicionMario(posicionActual[0] + 1, posicionActual[1]);
    }
}

/**
 * Comprueba las colisiones de mario con el mapa
 */
void Mundo::checkeoColisiones()
{
    // mario muere si se cae al vacio
    if (posicionActual[0] == anchoMundo - 1)
    {
        setEstadoMario("Muerto");
    }
    // mario gana si llega al borde derecho
    else if (posicionActual[1] == largoMundo - 1)
    {
        setEstadoMario("Ganador");
    }
    if (posicionActual[0] != anchoMundo - 1 && mapa[posicionActual[0] + 1][posicionActual[1]] == 0)
    {
        // si mario esta en el aire cae a 1 bloque x ejecucion
        checkeoGravedad();
    }
}

/**
 * Obtiene el estado de mario
 *
 */
void Mundo::getEstadoMario()
{
    cout << estadoMario << endl;
}

/**
 * Cambia el estado de mario
 * @param estado nuevo estado de mario
 */
void Mundo::setEstadoMario(string estado)
{
    estadoMario = estado;
    getEstadoMario();
}

/**
 * realiza una comprobacion inicial para ver si mario esta flotando
 * @return void
 */
void Mundo::comprobacionInicialMario()
{
    actualizarPosicionMario(posicionActual[0], posicionActual[1]);
}