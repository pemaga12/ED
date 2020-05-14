#include "lista.h"
#include "diccionario.h"
#include <iostream>
#include <string>
using namespace std;



// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
  public:
    string alumno;
    int nota;	
	Puntuacion(const string& nombre, int puntuacion): alumno(nombre), nota(puntuacion) {}
};


void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	  // A IMPLEMENTAR 
	Lista<string>::ConstIterator i = bien.cbegin();
	Lista<string>::ConstIterator e = mal.cbegin();
	Lista<Puntuacion>::Iterator b = listado.begin();
	
	Diccionario<string, int> auxiliar;
	Diccionario<string, int>::Iterator it = auxiliar.begin();
	
	while (i != bien.cend()) {
		string nombre = i.elem();
		bool esta = auxiliar.contiene(nombre);
		if (!esta) {//En caso de que el nombre no exista
			auxiliar.inserta(nombre, 1);
		}
		else {												//En caso de que el nombre ya exista
			it = auxiliar.busca(nombre);
			int nota = it.valor();
			nota++;
			auxiliar.inserta(nombre, nota);
		}
		i.next();
	}

	while (e != mal.cend()) {
		string nombre = e.elem();
		bool esta = auxiliar.contiene(nombre);
		if (!esta) {										//En caso de que el nombre no exista
			auxiliar.inserta(nombre, -1);
		}
		else {												//En caso de que el nombre ya exista
			it = auxiliar.busca(nombre);
			int nota = it.valor();
			nota--;
			auxiliar.inserta(nombre, nota);
		}
		e.next();
	}

	it = auxiliar.begin();

	while (it != auxiliar.end()) {
		Puntuacion alumnaux = Puntuacion(it.clave(), it.valor());
		if (alumnaux.nota != 0) {
			listado.pon_ppio(alumnaux);
		}
		it.next();
	}
}




void imprimePuntuaciones(Lista<Puntuacion>& listado) {
  Lista<Puntuacion>::ConstIterator i = listado.cbegin();
  Lista<Puntuacion>::ConstIterator e = listado.cend();
  while (i != e) {
	  cout << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
      i.next();	  
  }  
  cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			string resultado;
			cin >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

int main() {
  string comienzo;
  while (cin >> comienzo) {
	 Lista<string> bien;
	 Lista<string> mal;
	 Lista<Puntuacion> listado;
	 leeResultados(bien, mal);
	 califica(bien, mal,listado);
	 imprimePuntuaciones(listado);
  }
  return 0;   
}