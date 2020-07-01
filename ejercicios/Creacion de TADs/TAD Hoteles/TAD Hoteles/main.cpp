#include <iostream>
#include <string>
#include "hoteles.h"

using namespace std;

void alojar(Hoteles<string, string> &h);
void desalojar(Hoteles<string, string>& h);
void buscarHotel(Hoteles<string, string>& h);
void listadoHoteles(Hoteles<string, string>& h);
void listadoHuespedes(Hoteles<string, string>& h);

int main() {
	int opcion;
	Hoteles<string, string> hoteles;
	while (opcion != 0) {
		cout << "-----Bienvenido al sistema de reservas-----" << endl <<
			"1. Alojar huesped en un hotel" << endl <<
			"2. Desalojar un huesped de el hotel en el que este" << endl <<
			"3. Buscar el hotel en el que se aloja un huesped" << endl <<
			"4. Listado de hoteles dados de alta" << endl <<
			"5. Listado de huespedes en el sistema" << endl <<
			"0. Salir" << endl << ">";
		cin >> opcion;
		switch (opcion){
		case 1: alojar(hoteles); break;
		case 2: desalojar(hoteles); break;
		case 3: buscarHotel(hoteles); break;
		case 4: listadoHoteles(hoteles); break;
		case 5: listadoHuespedes(hoteles); break;
		}
	}
	

}

void alojar(Hoteles<string, string>& h) {
	string c, hotel;
	cin >> c;
	cin >> hotel;
	h.aloja(c, hotel);
	system("pause");
}

void desalojar(Hoteles<string, string>& h) {
	string hotel;
	cin >> hotel;
	h.desaloja(hotel);
	system("pause");
}

void buscarHotel(Hoteles<string, string>& h) {
	Lista<string> hoteles = h.listado_hoteles();


}

void listadoHoteles(Hoteles<string, string>& h)
{
}

void listadoHuespedes(Hoteles<string, string>& h)
{
}
