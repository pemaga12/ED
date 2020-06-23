/**
Este programa lee árboles de la entrada estándar, 
codificados de acuerdo con las siguientes reglas:
(1) El árbol vacío se codifica como #
(2) Los árboles simples se codifican como [v], con  
    v el valor del nodo
(3) Los árboles complejos se codifican como (IvD),
    con I la codificación del hijo izquierdo,
	v el valor de la raíz, y D la codificación
	del hijo derecho.
Para cada árbol leído, escribe en la salida estándar
el número de nodos singulares de dicho árbol.
	
Algunos casos representativos:

#
[0]
[5]
(([4]3[-3])1[-4])

-El primero representa el árbol vacío. Al no tener nodos,
un árbol vacío tiene 0 nodos sigulares.
-El segundo representa un árbol con un único nodo, cuyo valor
es 0. Dicho nodo es singular, ya que: (i) como no tiene 
ascestros, la suma de los ancestros es 0, (ii) como no
tiene descendientes, la suma de los descendientes es 0. 
-El tercero representa otro árbol con un único nodo, cuyo
valor es 5. Por la misma razón que en el segundo ejemplo,
este nodo es singular.
-El cuarto representa el siguiente árbol:
     
	       1
		  /  \
		  3  -4
         / \  
        4  -3 

Este árbol tiene 2 nodos sigulares: la raíz, y la raíz del hijo 
izquierdo. 

Por tanto, la salida del programa para estos casos será:

0
1
1
2

Algunos casos de prueba más:

ENTRADAS
(((#-2[-2])0#)0[-1])
(#-1[0])
([2]1[2])
(#-2(((#0([2]0(((((#1#)0(#0#))0(#-1[-2]))0(((#0#)2#)0[2]))0#)))2#)-1#))
((((#0[1])1#)1((#2(([-2]1#)1([2]1#)))0#))0(#0(#2[-1])))

SALIDAS ASOCIADAS
1
1
0
0
1

([25]20[22])

*/
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;
bool comprueba_arbol_aux(const Arbin<int>& a, bool resultado, int& profundidad);
bool comprueba_arbol(const Arbin<int>& a, int& profundidad);
bool esHoja(const Arbin<int>& a);
bool comprueba_hijos(const Arbin<int>& a);


/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
*/
bool comprueba_arbol(const Arbin<int>& a, int& profundidad) {
	// A IMPLEMENTAR
	bool resultado = true;
	profundidad = 0;
	if (a.esVacio()) return false;		//En caso de que el arbol sea vacío
	else {
		resultado = comprueba_arbol_aux(a, resultado, profundidad + 1);
	}
}

bool comprueba_arbol_aux(const Arbin<int>& a, bool resultado, int& profundidad) {
	if (!esHoja(a)){
		if (!comprueba_hijos(a)) {
			return false;
		}
	}
	else {
		resultado = comprueba_arbol_aux(a.hijoIz(), resultado, profundidad + 1);
		resultado = comprueba_arbol_aux(a.hijoDer(), resultado, profundidad + 1);
	}
	return resultado;
}

bool comprueba_hijos(const Arbin<int>& a) {
	bool bien = true;
	if (!a.hijoDer().esVacio() || !a.hijoDer().esVacio()) {
		if ((a.hijoDer().raiz() + 18) > a.raiz() + 18 || (a.hijoIz().raiz() + 18) > a.raiz() + 18) {
			bien = false;
		}
		if (a.hijoIz().raiz() < (a.hijoDer().raiz() + 2)) {
			bien = false;
		}
	}
	return bien;
}

bool esHoja(const Arbin<int>& a) {
	if (!a.hijoDer().esVacio() && !a.hijoDer().esVacio()) return false;
	return true;
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
	int profundidad;
	while (cin.peek() != EOF)  {
		cout << comprueba_arbol(lee_arbol(cin), profundidad) << endl << profundidad;
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}