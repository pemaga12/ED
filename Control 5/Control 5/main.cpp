#include <iostream>
using namespace std;
#include <string>
#include <stack>
#include "lista.h"
// INCLUIR EL RESTO DE TADS QUE SE CONSIDEREN OPORTUNOS
bool esVocal(const char c);

void invierteSecuenciasNoVocales(Lista<char> &mensaje) {
	Lista<char>::Iterator aux = mensaje.begin();
	stack<char> pila;

	while (aux != mensaje.end()) {
		char l = aux.elem();
		string caso = "";
		if (esVocal(l)) {
			while (!pila.empty()) {
				mensaje.insertar(pila.top(), aux);
				pila.pop();
			}
			aux.next();
		}
		else {
			pila.push(aux.elem());
			aux = mensaje.eliminar(aux);
		}
	}
	if (aux == mensaje.end()) {
		while (!pila.empty()) {
			mensaje.insertar(pila.top(), aux);
			pila.pop();
		}
	}
	// A IMPLEMENTAR
}

bool esVocal(const char c){
	switch (tolower(c)) {
		case 'a':return true;
		case 'e':return true;
		case 'i':return true;
		case 'o':return true;
		case 'u':return true;
		default: return false;
	}
}

 
// Imprime la lista por la salida estandar
void imprime(const Lista<char>& l) {
	l.print();
	cout << endl;
}


// Codifica el mensaje
void codifica(Lista<char>& mensaje) {
	invierteSecuenciasNoVocales(mensaje);
	mensaje.enredar();
}

  // Transforma la linea en una lista de caracteres
void construyeMensaje(const string& linea, Lista<char>& mensaje) {
	for(unsigned int i=0; i < linea.size(); i++)
		mensaje.pon_final(linea[i]);  
}

int main() {
	string linea;
	while(getline(cin,linea)) {
	   Lista<char> mensaje;
	   construyeMensaje(linea,mensaje);
       codifica(mensaje);
	   imprime(mensaje);
	}
	return 0;
}	
