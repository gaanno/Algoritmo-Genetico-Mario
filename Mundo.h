/*
    Archivo encargado de leer el mapa en formato txt y de manejar el movimiento
    @author Gabriel Norambuena
*/

#include <iostream>
#include <string>  
#include <fstream> 
#include <sstream> 
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
    bool codigoEjecutandose = true;

    // relacionado con el mundo
    void abrirMundo();
    void crearMapa();
    void imprimirMapa();

    // relacionado con el movimiento
    void moverDerecha();
    void moverIzquierda();
    void moverSaltoAlto();
    void moverSaltolargo();
    void getMovimientosMario();

    // relacionado con mario
    void getPosicionActual();
    void getEstadoMario();


private:
    //  relacionado con el mundo 
    string nombreMundo;
    int largoMundo;
    int anchoMundo;
    int bloqueReemplazado; // bloque que es reemplazado cuando mario se mueve en el
    int **mapa = nullptr;

    //  relacionado con mario 
    // posicionAnterior: derecha, izquierda, arriba, abajo, es la posicion anterior de mario para saber de donde proviene
    // util para el enfrentamiento de un enemigo
    string posicionAnterior = "inicio";
    string estadoMario = "vivo";
    int posicionActual[2]; // coordenadas fila, columna
    int enemigosDerrotados = 0;
    void setEstadoMario(string estado);

    //  relacionado con el movimiento 
    bool movimientoEjecutandose = false;
    int movimientosRestantes = 0;
    vector<char> movimientosMario;
    void checkeoGravedad();
    void checkeoColisiones();
    void comprobacionInicialMario();
    void checkeoColisionLimites();
    void checkeoColisionEnemigos();
    void alternarEstadoMovimiento();
    void actualizarPosicionMario(int fila, int columna);

    // realiza el movimiento en 1 bloque
    void movimientoUnitarioArriba();
    void movimientoUnitarioAbajo();
    void movimientoUnitarioDerecha();
    void movimientoUnitarioIzquierda();
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
    cout << endl;
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
 * Obtiene la posicion de mario
 */
void Mundo::getPosicionActual()
{
    cout << "Posicion actual: " << posicionActual[0] << " " << posicionActual[1] << endl;
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
    if (estadoMario == "vivo")
    {
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
    codigoEjecutandose = false;
}

/**
 * realiza una comprobacion inicial para ver si mario esta flotando
 */
void Mundo::comprobacionInicialMario()
{
    actualizarPosicionMario(posicionActual[0] + 1, posicionActual[1]);
}

/**
 * Comprueba si mario choco con un enemigo
 */
void Mundo::checkeoColisionEnemigos()
{
    if (estadoMario == "vivo" && bloqueReemplazado == 2 && posicionAnterior != "arriba")
    {
        setEstadoMario("Muerto: choco con un enemigo desde " + posicionAnterior);
    }
}

/**
 * Cambia el estado de movimiento
 * si se esta ejecutando lo detiene y viceversa
 */
void Mundo::alternarEstadoMovimiento()
{
    movimientoEjecutandose = !movimientoEjecutandose;
}

// MOVIMIENTO ------------------------------------------------------------------
/**
 * Realiza un movimiento hacia la derecha
 */
void Mundo::moverDerecha()
{
    movimientosMario.push_back('d');
    movimientoEjecutandose = true;
    movimientosRestantes = 1;
    movimientoUnitarioDerecha();
    movimientoEjecutandose = false;
}

/**
 * Realiza un movimiento hacia la izquierda
 */
void Mundo::moverIzquierda()
{
    movimientosMario.push_back('i');
    movimientoEjecutandose = true;
    movimientosRestantes = 1;
    movimientoUnitarioIzquierda();
    movimientoEjecutandose = false;
}

void Mundo::moverSaltoAlto()
{
    movimientosMario.push_back('s');
    movimientoEjecutandose = true;
    movimientosRestantes = 5;
    // +1 eje y → +1 eje y → +1 eje x → -1 eje y → -1 eje y.
    // +2 y
    movimientoUnitarioArriba();
    movimientoUnitarioArriba();

    // +1 x
    movimientoUnitarioDerecha();

    // -2 y
    movimientoUnitarioAbajo();
    movimientoUnitarioAbajo();

    movimientoEjecutandose = false;
}

void Mundo::moverSaltolargo()
{
    movimientosMario.push_back('j');
    movimientoEjecutandose = true;
    movimientosRestantes = 5;
    // +1 eje y → +1 eje x → +1 eje x → -1 eje x → -1 eje y.

    // +1 y
    movimientoUnitarioArriba();

    // +3 x
    movimientoUnitarioDerecha();
    movimientoUnitarioDerecha();
    movimientoUnitarioDerecha();

    // -1 y
    movimientoUnitarioAbajo();

    movimientoEjecutandose = false;
}

void Mundo::movimientoUnitarioArriba()
{
    if (movimientoEjecutandose)
    {
        getPosicionActual();
        posicionAnterior = "abajo";
        int fila = posicionActual[0] - 1;
        int columna = posicionActual[1];
        actualizarPosicionMario(fila, columna);
    }
}

void Mundo::movimientoUnitarioAbajo()
{
    if (movimientoEjecutandose)
    {
        posicionAnterior = "arriba";
        int fila = posicionActual[0] + 1;
        int columna = posicionActual[1];
        actualizarPosicionMario(fila, columna);
    }
}

void Mundo::movimientoUnitarioDerecha()
{
    if (movimientoEjecutandose)
    {
        posicionAnterior = "izquierda";
        int fila = posicionActual[0];
        int columna = posicionActual[1] + 1;
        actualizarPosicionMario(fila, columna);
    }
}

void Mundo::movimientoUnitarioIzquierda()
{
    if (movimientoEjecutandose)
    {
        posicionAnterior = "derecha";
        int fila = posicionActual[0];
        int columna = posicionActual[1] - 1;
        actualizarPosicionMario(fila, columna);
    }
}

// MOVIMIENTO ------------------------------------------------------------------
/***
 * Actualiza la posicion de mario en el mapa
 *
 */
void Mundo::actualizarPosicionMario(int fila, int columna)
{
    // movimientos que quedan por mover
    movimientosRestantes--;

    if (movimientosRestantes == 0)
    {
        movimientoEjecutandose = false;
    }

    if ((fila < 0 && posicionAnterior == "derecha") || (fila < 0 && posicionAnterior == "abajo"))
    {
        // limite izquierda o derecho, no lo muevo
        movimientoEjecutandose = false;
        movimientosRestantes = 0;
        checkeoColisiones();
        // cout << "limite izquierdo o superior" << endl;
        return;
    }

    else if (mapa[fila][columna] != 1)
    {
        bloqueReemplazado = mapa[fila][columna];
        //cout << "Bloque reemplazado: " << bloqueReemplazado << endl;
        mapa[posicionActual[0]][posicionActual[1]] = 0;
        posicionActual[0] = fila;
        posicionActual[1] = columna;
        mapa[fila][columna] = 3;
        imprimirMapa();
    }
    else
    {
        //cout << "choque bloque 1, bajando..." << endl;
        movimientosRestantes = 0;
        movimientoEjecutandose = false;
    }
    checkeoColisiones();
}

/**
 * Comprueba las colisiones de mario con su entorno
 */
void Mundo::checkeoColisiones()
{
    checkeoColisionLimites();
    checkeoGravedad();
    checkeoColisionEnemigos();
}

/**
 * Comprueba si mario esta volando
 */
void Mundo::checkeoGravedad()
{
    // si mario esta en el aire o sobre enemigo cae a 1 bloque x ejecucion
    if (estadoMario == "vivo" && !movimientoEjecutandose && mapa[posicionActual[0] + 1][posicionActual[1]] != 1)
    {
        posicionAnterior = "arriba";
        actualizarPosicionMario(posicionActual[0] + 1, posicionActual[1]);
    }
}

void Mundo::getMovimientosMario()
{
    for (int i = 0; i < movimientosMario.size(); i++)
    {
        cout << movimientosMario[i] << " ";
    }
}