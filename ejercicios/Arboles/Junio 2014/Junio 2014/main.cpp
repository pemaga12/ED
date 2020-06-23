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
string busca_camino_aux(const Arbin<string>& a, int contador, string puerta, int dragones);

/**
  COMPLEJIDAD: Explica aquí justificadamente cuál es la complejidad de 
               esta función
			   ***A COMPLETAR***
*/
 string busca_camino(const Arbin<string>& a) {
	 int contador = 0;			//guarda la cantidad de pasos que lleva
	 string puerta = "";		//guarda el nombre de la puerta
	 int dragones = 0;			//Guarda el numero de dragones del camino mas corto
	 if (a.esVacio()) {
		 return "";
	 }
	 else {
		 puerta = busca_camino_aux(a, contador, puerta, dragones);
	 }
	 return puerta;
}

 string busca_camino_aux(const Arbin<string>& a, int contador, string puerta, int dragones) {
	 if (a.raiz() == "dragon") contador++;
	 if (es_hoja(a)) {
		 if (contador < dragones) {
			 puerta = a.raiz();
			 dragones = contador;
		 }
	 }
	 else {
		 if (!a.hijoIz().esVacio()) {
			 busca_camino_aux(a.hijoIz(), contador, puerta, dragones);
		 }
		 if (!a.hijoDer().esVacio()) {
			 busca_camino_aux(a.hijoDer(), contador, puerta, dragones);
		 }
	 }
}

 bool es_hoja(Arbin<string> a) {
	 if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) return true;
	 else return false;
 }



Arbin<string> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<string>();
	case '[': {
		string raiz;
		in >> raiz;
  		in >> c;
		return Arbin<string>(raiz);
	}
	case '(': {
		Arbin<string> iz = lee_arbol(in);
		string raiz;
		in >> raiz;
		Arbin<string> dr = lee_arbol(in);
		in >> c;
		return Arbin<string>(iz, raiz, dr);
	}
	default: return Arbin<string>();
	}
}


int main() {
	Arbin<string> arbol;
	while (cin.peek() != EOF)  {
		cout << busca_camino(lee_arbol(cin)) << endl;
		string resto_linea;
		getline(cin, resto_linea);
		if (cin.peek() != EOF) cout << endl;
	}
	return 0;
}
