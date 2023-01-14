/*
    Mundo encargado de leer el mapa en formato txt
    @author Gabo
    @author Johan
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
    int bloqueReemplazado; // bloque que es reemplazado cuando mario se mueve en el
    int **mapa = nullptr;

    // relacionado con mario
    int posicionActual[2];
    
    // posicionAnterior: derecha, izquierda, arriba, abajo, es la posicion anterior de mario para saber de donde proviene
    // util para el enfrentamiento de un enemigo
    string posicionAnterior; 
    string estadoMario = "vivo";
    void actualizarPosicionMario(int fila, int columna);
    void setEstadoMario(string estado);

    // relacionado con el movimiento
    void checkeoGravedad();
    void checkeoColisiones();
    void comprobacionInicialMario();
    void checkeoColisionLimites();
    void checkeoColisionEnemigos();
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
    posicionAnterior = "izquierda";
    int fila = posicionActual[0];
    int columna = posicionActual[1] + 1;
    actualizarPosicionMario(fila, columna);
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
    bloqueReemplazado = mapa[fila][columna];
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
    // si mario esta en el aire cae a 1 bloque x ejecucion

    if (posicionActual[0] != anchoMundo - 1 && mapa[posicionActual[0] + 1][posicionActual[1]] == 0)
    {
        actualizarPosicionMario(posicionActual[0] + 1, posicionActual[1]);
    }
}

/**
 * Comprueba las colisiones de mario con su entorno
 * - colision bordes
 * - colision enemigo
 * - gravedad
 */
void Mundo::checkeoColisiones()
{
    checkeoColisionLimites();
    checkeoGravedad();
    checkeoColisionEnemigos();
}

/**
 * Comprueba las colisiones de mario con los limites del mapa
 * - Limite inferior: mario muere
 * - Limite derecho: mario gana
 */
void Mundo::checkeoColisionLimites()
{
    // si en el borde derecho no hay piso no importa, segun el pdf
    // el objetivo es solo llegar al final de la matriz segun mi interpretacion - gabo
    if (posicionActual[1] == largoMundo - 1)
    {
        setEstadoMario("Ganador");
    }
    // mario muere si se cae al vacio
    else if (posicionActual[0] == anchoMundo - 1)
    {
        setEstadoMario("Muerto: caida al vacio");
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
}

/**
 * realiza una comprobacion inicial para ver si mario esta flotando
 */
void Mundo::comprobacionInicialMario()
{
    actualizarPosicionMario(posicionActual[0], posicionActual[1]);
}

void Mundo::checkeoColisionEnemigos()
{
    if(bloqueReemplazado == 2 && posicionAnterior != "arriba"){
        setEstadoMario("Muerto: choco con un enemigo desde " + posicionAnterior);
    }
}