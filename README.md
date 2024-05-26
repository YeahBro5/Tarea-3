
## 8-Puzzle
## Descripción:

Este programa se encarga de solucionar un 8-Puzzle a través de distintos métodos de búsqueda, tanto Búsqueda en Profundidad (DFS) como Búsqueda en Anchura (BFS), dependiendo de la necesidad del usuario.

## Cómo compilar y ejecutar
Para mayor simplicidad al momento de probar y ejecutar el codigo se utilizará la plataforma [Repl.it](http://repl.it/), los pasos a seguir son:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "Create Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/YeahBro5/Tarea-3`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. Configure el comando de compilación con `gcc tdas/*.c tarea3.c -Wno-unused-result -o tarea3` y el comando run con (`./tarea3`).
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades
## Funcionando correctamente:
* `Búsqueda en Profundidad`: Utiliza el método DFS para encontrar la solución al 8-Puzzle.
* `Buscar en Anchura`: Utiliza el método BFS para encontrar la solución al 8-Puzzle.

## Problemas conocidos:
* Repetición de los movimientos

## A mejorar:
* Mejorar la estética del sistema para que sea mas atractivo para el usuario.
* Asegurarse de que no se repita ningun movimiento al estar realizando los estados adyacentes

## Ejemplo de uso:
**Paso 1: Búsqueda en Profundidad**
Se comienza a través del primer método de búsqueda, DFS
````
Opción seleccionada: 1) Búsqueda en Profundidad

Resuelto!!
Cantidad de estados visitados: 465251
Las acciones a realizar son: 
2 x 8 
1 3 4 
6 5 7 

2 8 x 
1 3 4 
6 5 7 
...
...

x 1 2 
3 4 5 
6 7 8 

````
Una vez resuelto se muestra la cantidad de estados vistados y las acciones a realizar para llegar al estado final

**Paso 2: Buscar en Anchura**

Después de utilizar el primer método, se puede verificar o encontrar un mejor camino a través del segundo método, BFS
````
Opción seleccionada: 2) Buscar en Anchura

Resuelto!!
Cantidad de estados visitados: 190887
Las acciones a realizar son: 
1 2 8 
x 3 4 
6 5 7 

1 2 8 
3 x 4 
6 5 7
...
...
x 1 2 
3 4 5 
6 7 8 

````
Al igual que en el primer método, una vez resuelto se muestra la cantidad de estados visitados y las acciones a realizar.

