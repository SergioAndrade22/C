#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"
#include "ColaCP.h"

typedef struct ciudad {
char *nombre;
float pos_x;
float pos_y;
} *TCiudad;

int comparador(TEntrada a, TEntrada b){
    int toRet;
    int *clave1;
    int *clave2;
    clave1 = a->clave;
    clave2 = b->clave;
    if (*clave1 > *clave2)
        toRet = 1;
    if (*clave1 == *clave2)
        toRet = 0;
    if (*clave1 < *clave2)
        toRet = -1;
    return toRet;
}

void ordenar_ascendente(TColaCP distancias, TLista* ciudades){
    TCiudad ciudad;
    while(cp_size(distancias) > 0){
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        ciudad = cp_eliminar(distancias)->valor;
        l_insertar(ciudades, NULL, ciudad);
    }
}

void ordenar_descendente(TColaCP distancias, TLista* ciudades){
    TCiudad ciudad;
    TLista invert;
    crear_lista(&invert);
    TPosicion reader;
    while (cp_size(distancias) > 0){
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        ciudad = cp_eliminar(distancias)->valor;
        l_insertar(&invert, NULL, ciudad);
    }
    reader = l_primera(invert);
    while (reader != NULL){
        ciudad = (TCiudad) malloc(sizeof(struct ciudad));
        ciudad = reader->elemento;
        l_insertar(ciudades, NULL, ciudad);
        if (reader == l_ultima(invert))
            reader = NULL;
        else
            reader = l_siguiente(invert, reader);
    }
}

void recalcular(TColaCP distancias, TCiudad actual){
    float* distancia;
    TLista store;
    crear_lista(&store);
    TCiudad auxC;
    TEntrada entr;
    TPosicion reader;
    while (cp_size(distancias) > 0){
        auxC = (TCiudad) malloc(sizeof(struct ciudad));
        auxC = cp_eliminar(distancias)->valor;
        l_insertar(&store, NULL, auxC);
    }
    reader = l_primera(store);
    while (reader != NULL){
        auxC = (TCiudad) malloc(sizeof(struct ciudad));
        auxC = reader->elemento;
        entr = (TEntrada) malloc(sizeof(struct entrada));
        distancia = (float*) malloc(sizeof(float));
        *distancia = abs(actual->pos_x - auxC->pos_x) + abs(actual->pos_y - auxC->pos_y);
        entr->clave = distancia;
        entr->valor = auxC;
        cp_insertar(distancias, entr);
        if (reader == l_ultima(store))
            reader = NULL;
        else
            reader = l_siguiente(store, reader);
    }
}

void optimizar_consumo(TColaCP distancias, TLista *ciudades){
    TCiudad actual;
    TLista invert;
    crear_lista(&invert);
    TPosicion reader;
    while (cp_size(distancias) > 0){
        actual = (TCiudad) malloc(sizeof(struct ciudad));
        actual = cp_eliminar(distancias)->valor;
        l_insertar(&invert, NULL, actual);
        if (cp_size(distancias) != 0)
            recalcular(distancias, actual);
    }
    reader = l_primera(invert);
    while (reader != NULL){
        actual = (TCiudad) malloc(sizeof(struct ciudad));
        actual = reader->elemento;
        l_insertar(ciudades, NULL, actual);
        if (reader == l_ultima(invert))
            reader = NULL;
        else
            reader = l_siguiente(invert, reader);
    }
}

int main(int argc, char* argv[]){
    /*
    if (argc != 2){
        printf("El programa necesita exactamente un parámetro.");
        return 1;
    }
    */
    int opt;
    opt = 0;
    printf("¡Bienvenido a su planificador de viajes! \n");
    printf("Por favor selecione, alguna de las siguientes opciones para operar: \n"
            "1: Mostrar ascendente, listaremos en pantalla las ciudades más cercana a usted, respecto a su posición actual. \n"
            "2: Mostrar descendente, listaremos en pantalla las ciudades más lejanas a usted, respecto a su posición actual. \n"
            "3: Reducir horas de manejo, listaremos las ciudades para maximizar el ahorro en combustible. \n"
            "4: Salir, concluye la ejecución del programa. \n");
    printf("Opción deseada: ");
    scanf("%d", &opt);
    //Creo las variables necesarias para guardar información
    TLista ciudades;
    crear_lista(&ciudades);
    TColaCP distancias;
    distancias = (struct cola_con_prioridad*) malloc(sizeof(struct cola_con_prioridad));
    crear_cola_cp(distancias, comparador);
    //Recupero el archivo a leer
    FILE* p1;
    p1 = fopen("Viajes.txt", "r");
    //Variables auxiliares que permiten recuperar los datos y recorrer las estructuras
    char* string;
    string = (char*) malloc(sizeof(char)*25);
    int ch;
    int i;
    int count;
    float* distancia;
    distancia = (float*) malloc(sizeof(float));
    float pos_usuarioX;
    float pos_usuarioY;
    pos_usuarioX = (ch = getc(p1)) - '0';
    ch = getc(p1);
    pos_usuarioY = (ch = getc(p1)) - '0';
    ch = getc(p1);
    i = 0;
    count = 0;
    TCiudad ciudad;
    ciudad = (struct ciudad*) malloc(sizeof(struct ciudad));
    TEntrada entr;
    entr = (struct entrada*) malloc(sizeof(struct entrada));
    TPosicion aux;
    //Recuperación y almacenamiento de los datos del archivo
    do{
        ch = getc(p1);
        if ((ch>=65 && ch<=90) || (ch>=97 && ch<=122)){
            string[i] = ch;
            i++;
        }
        else {
            if ((ch -'0')>=0 && (ch - '0')<=9){
                if (count == 0){
                    ciudad->pos_x = ch - '0';
                    count++;
                }
                if (count == 1){
                    ciudad->pos_y = ch - '0';
                }
            }
            else{
                if ((ch == '\n') || (ch == EOF)){
                    *distancia = abs(pos_usuarioX - ciudad->pos_x) + abs(pos_usuarioY - ciudad->pos_y);
                    ciudad->nombre = string;
                    entr->clave = distancia;
                    entr->valor = ciudad;
                    cp_insertar(distancias, entr);
                    string = (char*) malloc(sizeof(char)*25);
                    ciudad = (struct ciudad*) malloc(sizeof(struct ciudad));
                    entr = (struct entrada*) malloc(sizeof(struct entrada));
                    distancia = (float*) malloc(sizeof(float));
                    i = 0;
                    count = 0;
                }
            }
        }
    }while (ch != EOF);
    ciudad = (struct ciudad*) malloc(sizeof(struct ciudad));
    fclose(p1);
    //Funcionalidades del programa
    switch (opt){
        case 1 :
            ordenar_ascendente(distancias, &ciudades);
            aux = l_primera(ciudades);
            do{
                ciudad = aux->elemento;
                printf("%s \n", ciudad->nombre);
                if (aux == l_ultima(ciudades))
                    aux = NULL;
                else
                    aux = l_siguiente(ciudades, aux);
            }while (aux != NULL);
            break;
        case 2 :
            ordenar_descendente(distancias, &ciudades);
            aux = l_primera(ciudades);
            do{
                ciudad = aux->elemento;
                printf("%s \n", ciudad->nombre);
                if (aux == l_ultima(ciudades))
                    aux = NULL;
                else
                    aux = l_siguiente(ciudades, aux);
            }while (aux != NULL);
            break;
        case 3 :
            optimizar_consumo(distancias, &ciudades);
            aux = l_primera(ciudades);
            do{
                ciudad = aux->elemento;
                printf("%s \n", ciudad->nombre);
                if (aux == l_ultima(ciudades))
                    aux = NULL;
                else
                    aux = l_siguiente(ciudades, aux);
            }while (aux != NULL);
            break;
        case 4 :
            l_destruir(&ciudades);
            cp_destruir(distancias);
            free(string);
            free(distancia);
            free(ciudad);
            free(entr);
            printf("¡Disfrute su viaje!");
            return 0;
    }
    return 0;
}
