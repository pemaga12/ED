#include <iostream>
#include <string>
#include "pila.h"

using namespace std;

bool verifica(Pila<char> corchetes);
bool procesa(string texto);


int main() {
	string texto;
	cin >> texto;
	bool result = procesa(texto);
	if (result == true) cout << "La cadena esta bien hecha";
	else cout << "La cadena no esta bien hecha";
	system("pause");
	return 0;
}

bool procesa(string texto) {
	Pila<char> corchetes;
	for (unsigned int i = 0; i < texto.size(); i++) {
		if (texto[i] == '{' || texto[i] == '}') {
			corchetes.apila(texto[i]);
		}
	}
	bool result = verifica(corchetes);
	return result;
}

bool verifica(Pila<char> corchetes) {
	int abiertos = 0;
	int cerrados = 0;
	bool result = true;
	if (corchetes.cima() == '{') result = false;
	else {
		while (!corchetes.esVacia()) {
			if (corchetes.cima() == '{') abiertos++;
			else {
				cerrados++;
				corchetes.desapila();
				if (corchetes.cima() == '{') abiertos++;
				else result = false;
			}
			corchetes.desapila();
		}
	}
	if (abiertos != cerrados) result = false;
	return result;
}