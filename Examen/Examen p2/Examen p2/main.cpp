#include "Arbin.h"
#include <iostream>
#include <string>

/*
Pedro Martínez Gamero
51717322m
*/
using namespace std;
unsigned int numero_neutros_aux(const Arbin<int>& a, int& contador);
unsigned int cuenta_neutros_positivos_rama(const Arbin<int>& a, int neutro);

/** Indica aquí, razonadamente, la complejidad de numero_neutros
El coste será cuadrático ya que da pasa doblemente por cada nodo
*/

unsigned int numero_neutros(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int contador = 0;
	
	if (a.esVacio()) {
		return 0;
	}
	else {
		contador = numero_neutros_aux(a, contador);
	}
	return contador;
}

unsigned int numero_neutros_aux(const Arbin<int>& a, int& contador) {
	int neutroIz = 0;
	int neutroDer = 0;
	int contadorAux1 = 0;
	int contadorAux2 = 0;
	if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {		//En caso de que sea hoja
		contador = contador + 1;
		return contador;
	}
	else {
		//cuenta los positivos de cada rama
		if (!a.hijoIz().esVacio())
		neutroIz = cuenta_neutros_positivos_rama(a.hijoIz(), neutroIz);
		if(!a.hijoDer().esVacio())
		neutroDer = cuenta_neutros_positivos_rama(a.hijoDer(), neutroDer);
		
		if (neutroIz == neutroDer) contador = contador + 1;					//En caso de que el numero de neutros sea igual suma 1 
		
		//hace lo mismo con los nodos que tiene por debajo
		if (!a.hijoDer().esVacio())
		contador = numero_neutros_aux(a.hijoDer(), contador);
		if (!a.hijoIz().esVacio())
		contador = numero_neutros_aux(a.hijoIz(), contador);
	}
	return contador;
}

unsigned int cuenta_neutros_positivos_rama(const Arbin<int>& a, int neutro) {			//neutro es un contador de la cantidad de nodos positivos que hay en la rama
	if (a.raiz() > 0) {
		neutro = neutro + 1;
	}
	
		if (!a.hijoIz().esVacio())
		neutro = cuenta_neutros_positivos_rama(a.hijoIz(), neutro);
		if (!a.hijoDer().esVacio())
		neutro = cuenta_neutros_positivos_rama(a.hijoDer(), neutro);
	
	return neutro;

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
		Arbin<int> a = lee_arbol(cin);
		cout << numero_neutros(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
