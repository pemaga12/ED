#include <iostream>
#include <string>
#include "diccionario.h"
#include "lista.h"

using namespace std;

void leeTexto(Lista<string>& palabras);
void cuentaPalabras(Lista<string>& palabras, Diccionario<string, int>& contador);

int main() {
	Lista<string> palabras;
	Diccionario<string, int> contador;
	leeTexto(palabras);
	cuentaPalabras(palabras, contador);

	Diccionario<string, int>::ConstIterator it = contador.cbegin();
	while (it != contador.cend()) {
		cout << it.clave() << " " << it.valor() << endl;
		it.next();
	}
	return 0;
}

void leeTexto(Lista<string>& palabras) {			//Encargada de leer el texto
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			palabras.pon_final(nombre);
		}
	} while (nombre != "#");
}

void cuentaPalabras(Lista<string>& palabras, Diccionario<string, int>& contador){
	//Creamos iteradores para la lista palabras y para el diccionario
	Lista<string>::ConstIterator it = palabras.cbegin();
	Diccionario<string, int>::Iterator cont = contador.begin();

	//Recorremos la lista con todas las palabras
	while (it != palabras.cend()) {				
		if (contador.contiene(it.elem())) {				//si la palabra ya existe
			cont = contador.busca(it.elem());			//Devuelve la posicion en la que está la palabra
			cont.setVal(cont.valor() + 1);				//Suma la cantidad de veces que aparece
		}
		else {
			contador.inserta(it.elem(), 1);				//Inserta la palabra
		}
		it.next();
	}
}
