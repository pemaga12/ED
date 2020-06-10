#include <iostream>
#include <string>
#include "pila.h"

using namespace std;

string procesa(int numero);

int main() {
	int numero;
	cin >> numero;
	string resultado = procesa(numero);
	cout << resultado;
}

string procesa(int numero) {
	string cadenaFinal;
	Pila<int> pila;
	
	while (numero > 10) {
		int elem = numero % 10;
		numero = numero / 10;
		pila.apila(elem);
		if (numero < 10) pila.apila(numero);
	}
	int suma = 0;
	while (!pila.esVacia()) {
		int digito = pila.cima();
		pila.desapila();
		suma += digito;
		if(!pila.esVacia()) cadenaFinal = cadenaFinal + std::to_string(digito) + " + ";
		else cadenaFinal = cadenaFinal + std::to_string(digito) + " = " + std::to_string(suma);
	}
	return cadenaFinal;
}