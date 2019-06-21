#ifndef COLACP_H_INCLUDED
#define COLACP_H_INCLUDED

/// Puntero para la clave de la entrada
typedef void *TClave;

/// Puntero para el valor de la entrada
typedef void *TValor;

/// Puntura a un registro con clave y valor
typedef struct entrada {
    TClave clave;
    TValor valor;
} *TEntrada;

/// Puntero a registro con una entrada, y sus enlaces a sus nodos (padre, hijo izquierdo e hijo derecho)
typedef struct nodo {
    TEntrada entrada;
    struct nodo *padre;
    struct nodo *hijo_izquierdo;
    struct nodo *hijo_derecho;
} *TNodo;

/// Puntero a registro, con su entero a cantidad, y su nodo raíz
typedef struct cola_con_prioridad {
    unsigned int cantidad_elementos;
    TNodo raiz;
} *TColaCP;

/** Creación de la cola
@param Cola a crear
@param Funcion comparador
@return Cola inicializada
**/
TColaCP crear_cola_cp(TColaCP cola, int (*f)(TEntrada, TEntrada));

/** Inserta la entrada a cola
@param Cola en donde se va a insertar
@param Entrada a insertar
@return
**/
int cp_insertar(TColaCP cola, TEntrada entr);

/** Elimina la entrada con mayor prioridad
@param Cola
@return Entrada eliminada
**/
TEntrada cp_eliminar(TColaCP cola);

/** Retorna el tamaño de la cola
@param Cola
@return Tamaño de la cola
**/
int cp_size(TColaCP cola);

/** Destruye por completo la cola
@param Cola a destruir
@return Retorna si se elimino o no correctalemte la cola
**/
int cp_destruir(TColaCP cola);

#endif // COLACP_H_INCLUDED
