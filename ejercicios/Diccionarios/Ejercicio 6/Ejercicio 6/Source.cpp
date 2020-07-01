#include <iostream>
#include <string>
#include "DiccionarioHash.h"
#include "hash.h"
#include "lista.h"

using namespace std;

void leeLista(Lista<string>& val);
void rellenaDiccionario(DiccionarioHash<string, int> contador, Lista<string> lista);

int main() {
	Lista<string> val;
	DiccionarioHash<string, int> contador;
	leeLista(val);
	rellenaDiccionario(contador, val);

	DiccionarioHash<string, int>::ConstIterator it = contador.cbegin();
	while (it != contador.cend()) {
		cout << it.clave() << " " << it.valor() << endl;
		it.next();
	}
}

/*Funcion encargada de leer y rellenar la lista*/

void leeLista(Lista<string>& val){
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			val.pon_final(nombre);
		}
	} while (nombre != "#");
}

void rellenaDiccionario(DiccionarioHash<string, int> contador, Lista<string> lista){
	Lista<string>::ConstIterator it = lista.cbegin();
	
	while (it != lista.cend()) {
		if (contador.contiene(it.elem())) {
			DiccionarioHash<string, int>::Iterator dicc = contador.busca(it.elem());
			dicc.setVal(dicc.valor() + 1);
		}
		else {
			contador.inserta(it.elem(), 1);
		}
		it.next();
	}
}
