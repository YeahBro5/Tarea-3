#include <stdio.h>
#include <stdlib.h>
#include "tdas/list.h"
#include "tdas/extra.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <string.h>
#include <stdbool.h>

// Definición de la estructura para el estado del puzzle
typedef struct {
    int square[3][3]; // Matriz 3x3 que representa el tablero
    int x;    // Posición x del espacio vacío
    int y;    // Posición y del espacio vacío
    List* actions; //Secuencia de movimientos para llegar al estado
} State;

// Función para realizar una copia de un estado.
State* copiarEstado(const State* estado);

// Función para verificar si un estado es el estado final.
bool isFinal(State* estado);

// Función para imprimir el estado del puzzle.
void imprimirEstado(const State* estado);

// Función para mover el espacio vacío en el puzzle.
void moverEspacioVacio(State* estado, int x, int y, int nuevoX, int nuevoY);

// Función para obtener los estados adyacentes a un estado.
List* obtenerEstadosAdyacentes(State* estado);

// Función para mostrar la secuencia de acciones
void mostrarAcciones(List* listaAcciones);

// Función encargada del menú 1 "Búsqueda en Profundidad"
void dfs(State *estadoInicial);

// Función encargada del menú 2 "Buscar en Anchura"
void bfs(State *estadoInicial);

int main() {
    // Estado inicial del puzzle
    State estado_inicial = {
        {{0, 2, 8}, // Primera fila (0 representa espacio vacío)
         {1, 3, 4}, // Segunda fila
         {6, 5, 7}, // Tercera fila
         },  
        0, 0   // Posición del espacio vacío (fila 0, columna 0)
    };
    estado_inicial.actions = list_create();

    // Imprime el estado inicial
    printf("Estado inicial del puzzle:\n");
    imprimirEstado(&estado_inicial);

    int opcion;
    do {
        puts("========================================");
        puts("     Escoge método de búsqueda");
        puts("========================================");
        
        puts("1) Búsqueda en Profundidad");
        puts("2) Buscar en Anchura");
        puts("3) Salir");
    
        printf("Ingrese su opción: ");
        scanf(" %d", &opcion);
    
        switch (opcion) {
        case 1:
          dfs(&estado_inicial);
          break;
        case 2:
          bfs(&estado_inicial);
          break;
        }
        presioneTeclaParaContinuar();
        limpiarPantalla();

  } while (opcion != 3);

  return 0;
}

// Función para realizar una copia de un estado.
State* copiarEstado(const State* estado) {
    State* nuevoEstado = (State*)malloc(sizeof(State)); // Reserva de memoria para el nuevo estado
    memcpy(nuevoEstado, estado, sizeof(State)); // Copia del estado
    nuevoEstado->actions = list_create(); // Crea una nueva lista para las acciones
    return nuevoEstado;
}

// Función para verificar si un estado es el estado final.
bool isFinal(State* estado)
{
    State estadoDeseado = { // Estado buscado
        {{0, 1, 2}, // Primera fila (0 representa espacio vacío)
         {3, 4, 5}, // Segunda fila
         {6, 7, 8}, // Tercera fila
         }};
    for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
                {
                    if ((estadoDeseado.square[i][j]) != estado->square[i][j]) // Comparacion de las posiciones de las 2 matrices, en caso de que alguna sea distinta se retorna falso.
                    {
                        return false;
                    }
                }
        }

    return true;
}

// Función para imprimir el estado del puzzle
void imprimirEstado(const State* estado) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (estado->square[i][j] == 0)
                printf("x "); // Imprime un espacio en blanco para el espacio vacío
            else
                printf("%d ", estado->square[i][j]);
        }
        printf("\n");
    }
}

// Función para mover el espacio vacío en el puzzle.
void moverEspacioVacio(State* estado, int x, int y, int nuevoX, int nuevoY)
{
    int elemAIntercambiar = estado->square[nuevoX][nuevoY]; // Se guarda el elemento de la casilla a cambiar
    estado->square[nuevoX][nuevoY] = 0; // Se actualiza con el espacio vacio en la casilla a cambiar
    estado->square[x][y] = elemAIntercambiar; // Se inserta el elemento en la casilla donde estaba el espacio vacio
    
    // Actualización de los valores del espacio vacio
    estado->x = nuevoX; 
    estado->y = nuevoY;

}

// Función para obtener los estados adyacentes a un estado.
List* obtenerEstadosAdyacentes(State* estado)
{
    List* listaEstadosAdy = list_create(); // Creación de la lista para los estados
    // DEFINICIÓN DE LIMITES
    int limiteLateralIzq = 0;
    int limiteLateralDer = 2;
    int limiteSuperior = 0;
    int limiteInferior = 2;
    // Guardado de la posicion del espacio vacio.
    int x = estado->x;
    int y = estado->y;

    // Condiciones encargadas de ir moviendo el espacio vacio siempre y cuando no supere los limites establecidos.
    if (x - 1 >= limiteLateralIzq) // Mover a la izquierda
    {
        State* nuevoEstado = copiarEstado(estado); // Copia del estado actual
        moverEspacioVacio(nuevoEstado, x, y, x-1, y); // Se mueve el espacio a la izquierda

        // Se guardan los movimientos del estado anterior
        State* accion = list_first(estado->actions);
        while(accion) {
            list_pushBack(nuevoEstado->actions, accion);
            accion = list_next(estado->actions);
        }
        
        list_pushBack(nuevoEstado->actions, nuevoEstado); // Se guarda el movimiento actual
        list_pushBack(listaEstadosAdy, nuevoEstado); // Se agrega el nuevo estado a la lista de estados adyacentes
    }
    if (x + 1 <= limiteLateralDer) // Mover a la derecha
    {
        State* nuevoEstado = copiarEstado(estado);
        moverEspacioVacio(nuevoEstado, x, y, x+1, y); // Se mueve el espacio a la derecha


        State *accion = list_first(estado->actions);
        while(accion) {
            list_pushBack(nuevoEstado->actions, accion);
            accion = list_next(estado->actions);
        }

        list_pushBack(nuevoEstado->actions, nuevoEstado);
        list_pushBack(listaEstadosAdy, nuevoEstado);


    }
    if (y - 1 >= limiteSuperior) // Mover hacia arriba
    {
        State* nuevoEstado = copiarEstado(estado);
        moverEspacioVacio(nuevoEstado, x, y, x, y-1); // Se mueve el espacio hacia arriba
        State *accion = list_first(estado->actions);
        while(accion) {
            list_pushBack(nuevoEstado->actions, accion);
            accion = list_next(estado->actions);
        }

        list_pushBack(nuevoEstado->actions, nuevoEstado);
        list_pushBack(listaEstadosAdy, nuevoEstado);
    }
    if (y + 1 <= limiteInferior) // Mover hacia abajo
    {
        State* nuevoEstado = copiarEstado(estado);
        moverEspacioVacio(nuevoEstado, x, y, x, y+1); // Se mueve el espacio hacia abajo

        State *accion = list_first(estado->actions);
        while(accion) {
            list_pushBack(nuevoEstado->actions, accion);
            accion = list_next(estado->actions);
        }
        list_pushBack(nuevoEstado->actions, nuevoEstado);
        list_pushBack(listaEstadosAdy, nuevoEstado);
    }

    return listaEstadosAdy;
}

// Función para mostrar la secuencia de acciones
 void mostrarAcciones(List* listaAcciones)
     {
         // Recorrido de la lista para ir mostrando las acciones
         State *accion = list_first(listaAcciones);
         while(accion) {
             imprimirEstado(accion); // Para cada estado en la lista se imprime su matriz
             printf("\n");
             accion = list_next(listaAcciones);
         }


     }

// Función encargada del menú 1 "Búsqueda en Profundidad"
void dfs(State *estadoInicial)
{
    List* listaEstadosAdyacentes = list_create(); // Inicializacion de la lista
    int contador = 0; // Contador para los estados visitados
    Stack* pila = stack_create(pila); // Inicializacion de la pila a utilizar
    stack_push(pila, estadoInicial); // Se agrega el estado inicial a la pila

    while (stack_top(pila) != NULL) // Bucle hasta que la pila este vacia
        {
            contador++;
            // Se saca un estado de la pila
            State* estadoActual = stack_top(pila);
            stack_pop(pila);
            
            if (isFinal(estadoActual)) // Se revisa si el estado sacado es el estado final
            {
                // En caso de que lo sea, se muestra la información correspondiente.
                printf("Resuelto!!\n");
                printf("Cantidad de estados visitados: %d\n", contador);
                printf("Las acciones a realizar son: \n");
                mostrarAcciones(estadoActual->actions);
        
                // Liberación de memoria
                list_clean(estadoActual->actions);
                free(estadoActual);
                return;
            }
            // En caso de que la lista de acciones del estado actual supere las 15, se continua con el siguiente para asi no entrar en bucles infinitos
            if(list_size(estadoActual->actions) > 15){
                //Liberación de memoria
                list_clean(estadoActual->actions);
                free(estadoActual);

                continue;
            }
                // Se recorre la lista de estados adyacentes generados a partir del estado sacado en la pila y se van agregando para asi ser revisados.
                listaEstadosAdyacentes = obtenerEstadosAdyacentes(estadoActual);
                State* estadoAdyacente = (State*) list_first(listaEstadosAdyacentes);
                while(estadoAdyacente != NULL) {
                    stack_push(pila, estadoAdyacente);
                    estadoAdyacente= (State*) list_next(listaEstadosAdyacentes);
                }
                // Liberación de memoria
                list_clean(listaEstadosAdyacentes);
                list_clean(estadoActual->actions);
        }

    printf("No se logró encontrar una solución.\n");



    // Liberación de memoria
    free(pila);


}

// Función encargada del menú 2 "Buscar en Anchura"
void bfs(State *estadoInicial)
{
    List* listaEstadosAdyacentes = list_create(); // Inicializacion de la lista
    int contador = 0;
    Queue* cola = queue_create(cola); // Inicializacion de la cola
    queue_insert(cola, estadoInicial); // Se inserta el estado inicial en la cola

    while(queue_front(cola) != NULL)
        {
            contador++;
            // Se saca un estado de la cola
            State* estadoActual = queue_front(cola);
            queue_remove(cola);
            
            if (isFinal(estadoActual)) // Para cada estado extraido se revisa si es el estado final
            {
                // En caso de que lo sea se muestra la información
                printf("Resuelto!!\n");
                printf("Cantidad de estados visitados: %d\n", contador);
                printf("Las acciones a realizar son: \n");
                mostrarAcciones(estadoActual->actions);
                list_clean(estadoActual->actions);
                free(estadoActual);
                return; 
            }

            // Para cada estado extraido se revisa si su lista de acciones de mayor que 15, en caso de que lo sea se pasa al siguiente
            if(list_size(estadoActual->actions) > 15){
                //Liberacion de memoria
                list_clean(estadoActual->actions);
                free(estadoActual);
                
                continue;
            }

            // Se sacan los estados adyacentes del estado extraido y se agregan a a cola.
            listaEstadosAdyacentes = obtenerEstadosAdyacentes(estadoActual);
            State* estadoAdyacente = (State*) list_first(listaEstadosAdyacentes);
                while(estadoAdyacente != NULL) 
                {
                    queue_insert(cola, estadoAdyacente);
                    estadoAdyacente= (State*) list_next(listaEstadosAdyacentes);
                }
            // Liberación de memoria
            list_clean(listaEstadosAdyacentes);
            list_clean(estadoActual->actions);

        }
    
    printf("No se logró encontrar una solución");

}