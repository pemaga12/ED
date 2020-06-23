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

Supondremos que dragones = 0, caballero = 1 y princesa = 2.
(([2]0[2])1([2]1#))
(([2]1[2])1([2]0#))
(([2]1[2])1([2]1#))

*/
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;
bool es_izquierdo_aux(const Arbin<int>& a, int contador, int auxI, int auxD);
bool esHoja(Arbin<int>& a);

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
*/
bool esIzquierdo(const Arbin<int>& a) {
	// A IMPLEMENTAR
	bool izquierdo = false;
	int contador = 0;
	int auxI = 0;
	int auxD = 0;
	if (a.esVacio()) return true;		//En caso de que el arbol sea vacío
	else {
		izquierdo = es_izquierdo_aux(a, contador, auxI, auxD);
	}
	return izquierdo;
}

bool es_izquierdo_aux(const Arbin<int>& a, int contador, int auxI, int auxD) {
	if(esHoja(a) )
}

bool esHoja(Arbin<int>& a) {
	if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) { return true; }
	else return false;
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
	while (cin.peek() != EOF)  {
		cout << numero_princesas(lee_arbol(cin)) << endl;
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
