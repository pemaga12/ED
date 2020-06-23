#include "cola.h"
#include <iostream>
using namespace std;

/**
Este programa lee por la entrada est�ndar lineas con el siguiente formato:
- Una secuencia de enteros (excluido el -1), que se interpreta como una
  cola.
- El -1
- Una posici�n
- Un desplazamiento
Entonces, ejecuta la operaci�n 'desplazar' sobre la cola indicada, y escribe
por pantalla el resultado (o POSICION_INVALIDA en caso de que la posici�n
no sea v�lida)

Ejemplo de entrada:

1 2 3 4 5 -1 4 2
1 2 3 4 5 -1 4 1
1 2 3 4 5 -1 4 0
1 2 3 4 5 -1 4 3
1 2 3 4 5 -1 4 20
1 2 3 4 5 -1 5 2
1 2 3 4 5 -1 5 1
1 2 3 4 5 -1 5 0
1 2 3 4 5 -1 5 3
1 2 3 4 5 -1 5 4
1 2 3 4 5 -1 5 20
1 2 3 4 5 -1 80 20
-1 1 1

Salida producida:

1 4 2 3 5
1 2 4 3 5
1 2 3 4 5
4 1 2 3 5
4 1 2 3 5
1 2 5 3 4
1 2 3 5 4
1 2 3 4 5
1 5 2 3 4
5 1 2 3 4
5 1 2 3 4
POSICION_INVALIDA
POSICION_INVALIDA

*/

void muestra_cola(Cola<int>& cola) {
   while(! cola.esVacia()) {
	   cout << cola.primero() << " ";
	   cola.quita();
   }	
   cout << endl;
}

bool lee_cola(Cola<int>& cola) {
	int v;
	if (cin >> v) {
	   while (v != -1) {
		  cola.pon(v);
		  cin >> v;
	   }
	   return true;
	}
	else return false;
}

int main() {
	Cola<int> cola;
	while (lee_cola(cola)) {
		int pos, desp;
		cin >> pos >> desp;
		try {              
			cola.desplaza(pos, desp);
			muestra_cola(cola);
		}
		catch (EPosicionInvalida) {
			cout << "POSICION_INVALIDA" << endl;
			cola = Cola<int>();
		}
	}
}