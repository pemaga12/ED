#include <iostream>
#include <string>
#include "Arbin.h"

using namespace std;

unsigned int auxiliar(const Arbin<int>& a, unsigned int k, unsigned int j);
int cuentaNodosAux(Arbin<int> a, int contador);
int cuentaNodos(Arbin<int> a);
bool esHoja(Arbin<int> a);
int cuentaHojasAux(Arbin<int> a, int contador);
int cuentaHojas(Arbin<int> a);
int talla(Arbin<int> a);
int tallaAux(Arbin<int> a, int contador, int &altura);

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

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF) {
		Arbin<int> a = lee_arbol(cin);
		int k;
		cin >> k;
		cout << numero_hojas_mas_profundas_que(a, k) << endl;
		cout << cuentaNodos(a) << endl;
		cout << esHoja(a) << endl;
		cout << cuentaHojas(a) << endl;
		cout << talla(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}

/*
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
([2]1([4]3([6]5[7]))) 0
*/



int cuentaNodos(Arbin<int> a) {
	int contador = 0;
	if (a.esVacio()) {
		return 0;
	}
	else {

		contador = cuentaNodosAux(a, contador + 1);
	}
	return contador;
}

int cuentaNodosAux(Arbin<int> a, int contador) {
	if (a.esVacio()) {
		return contador;
	}
	else {

		if (!a.hijoDer().esVacio()) {
			contador = cuentaNodosAux(a.hijoDer(), contador + 1);
		}
		if (!a.hijoIz().esVacio()) {
			contador = cuentaNodosAux(a.hijoIz(), contador + 1);
		}
	}
	return contador;
}

bool esHoja(Arbin<int> a) {
	if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) return true;
	else return false;
}

int cuentaHojas(Arbin<int> a) {
	int contador = 0;
	if (a.esVacio()) {
		return 0;
	}
	else {
		contador = cuentaHojasAux(a, contador);
	}
	return contador;
}

int cuentaHojasAux(Arbin<int> a, int contador) {
	if (a.esVacio()) {
		return contador;
	}
	else {
		if (esHoja(a)) {
			contador++;
		}
		if (!a.hijoDer().esVacio()) {
			contador = cuentaHojasAux(a.hijoDer(), contador);
		}
		if (!a.hijoIz().esVacio()) {
			contador = cuentaHojasAux(a.hijoIz(), contador);
		}
	}
	return contador;
}

int talla(Arbin<int> a) {
	int contador = 0;
	int altura = 0;
	if (a.esVacio()) {
		return 0;
	}
	else {
		contador = cuentaHojasAux(a, contador);
	}
	return contador;
}

int tallaAux(Arbin<int> a, int contador, int &altura){
	if (a.esVacio()) {
		return contador;
	}
	else {
		if (esHoja(a)) {
			if (altura < contador) altura = contador; 
			contador = 0;
		}
		if (!a.hijoDer().esVacio()) {
			contador = cuentaNodosAux(a.hijoDer(), contador + 1);
		}
		if (!a.hijoIz().esVacio()) {
			contador = cuentaNodosAux(a.hijoIz(), contador + 1);
		}
	}
	return contador;
}
