#include <iostream>
#include <string>
#include "pila.h"

using namespace std;

void procesaCadena(string cadena);
string creaCadena(Pila<char> pila);

int main() {
	string cadena;
	cin >> cadena;
	procesaCadena(cadena);
	system("pause");
}

void procesaCadena(string cadena) {
	Pila<char> pila;
	for (int i = 0; i < cadena.size(); i++) {
		pila.apila(cadena[i]);
	}
	string result = creaCadena(pila);
	cout << result;
}

string creaCadena(Pila<char> pila) {
	string result;
	if (pila.esVacia()) return "";
	else {
		result = pila.cima();
		pila.desapila();
		result = result + creaCadena(pila);
		return result;
	}
}