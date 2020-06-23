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



*/
#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;

unsigned int aux_numero_singulares(const Arbin<int>& a, unsigned int contador, int suma);
unsigned int suma_descendientes(const Arbin<int>& a, int suma);

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
*/
unsigned int numero_singulares(const Arbin<int>& a) {
	unsigned int contador = 0;	//En esta variable se almacena la cantidad de nodos singulares
	int suma = a.raiz();		//En esta variable se almacenará la suma de los valores anteriores
	if (a.esVacio()) {	//En caso de que el arbol esté vacío
		return 0;
	}
	else {
		contador = aux_numero_singulares(a, contador, suma);
	}
	return contador;
}

unsigned int aux_numero_singulares(const Arbin<int>& a, unsigned int contador, int suma) {
	int aux = suma_descendientes(a, 0);
	if (suma == aux) {
		contador++;
	}
	suma += a.raiz();
	if (a.esVacio()) {
		return contador;
	}
	else {
		if (!a.hijoDer().esVacio()) {
			contador = aux_numero_singulares(a.hijoDer(), contador, suma);
		}
		if (!a.hijoIz().esVacio()) {
			contador = aux_numero_singulares(a.hijoIz(), contador, suma);
		}
	}
	return contador;
}

unsigned int suma_descendientes(const Arbin<int>& a, int suma) {
	if (a.esVacio()) {
		return 0;
	}
	else {
		suma += a.raiz();
		if (!a.hijoDer().esVacio()) {
			suma = suma_descendientes(a.hijoDer(), suma);
		}
		if (!a.hijoIz().esVacio()) {
			suma = suma_descendientes(a.hijoIz(), suma);
		}
	}
	return suma;
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
		cout << numero_singulares(lee_arbol(cin)) << endl;
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
