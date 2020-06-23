#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

unsigned int auxiliar(const Arbin<int>& a, unsigned int k, unsigned int j);
int cuentaNodosAux(Arbin<int> a, int contador);
bool esHoja(Arbin<int> a);
int cuentaHojas(Arbin<int> a);
int cuentaHojasAux(Arbin<int> a, int contador);


/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   
			   La complejidad es lineal debido a que se recorre todo el arbol.

*/
unsigned int numero_hojas_mas_profundas_que(const Arbin<int>& a, unsigned int k) {
	// A IMPLEMENTAR
	int j = 0;																			//Profundidad actual
	int n = 0;																			//Numero de hojas
	
	if (!a.esVacio()) { 
		if (a.hijoDer().esVacio() && a.hijoIz().esVacio() && k <= j) n = 1;
		else n = auxiliar(a.hijoDer(), k, j + 1) + auxiliar(a.hijoIz(), k, j + 1); 
	}
	return n;
}

unsigned int auxiliar(const Arbin<int>& a, unsigned int k, unsigned int j) {
	if (a.esVacio()) {
		return 0;
	}

	else if (a.hijoDer().esVacio() && a.hijoIz().esVacio() && k <= j) {
		return 1;
	}

	else if (a.hijoDer().esVacio() && a.hijoIz().esVacio() && k > j) {
		return 0;
	}

	else {
		return auxiliar(a.hijoDer(), k, j + 1) + auxiliar(a.hijoIz(), k, j + 1);
	}
}



Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}




/**
La entrada al programa consiste de líneas formadas por:
(1) Un árbol de enteros
(2) El valor de k
Los árboles se codifican de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada línea leida, escribe en la salida estádar
el número de hojas que están a profundidad mayor que k

	
Ejemplo de entrada:

([2]1([4]3[5])) 0
([2]1([4]3[5])) 1
([2]1([4]3[5])) 2
([2]1([4]3[5])) 3
([2]1([4]3[5])) 4
([2]1([4]3[5])) 100

Salida asociada:

3
3
2
0
0
0

*/


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a,k) << endl;
		cout << cuentaNodos(a)<< endl;
		cout << esHoja(a) << endl;
		cout << cuentaHojas(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
