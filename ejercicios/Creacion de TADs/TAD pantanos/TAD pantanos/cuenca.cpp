#include "cuenca.h"
#include <string>

using namespace std;

Cuenca::Cuenca() {};

void Cuenca::insertar_rio(const string& r) {
	if (_rios.contiene(r)) {
		throw ERioDuplicado{};
	}
	else {
		_rios.inserta(r, DiccionarioHash<string, info_pantano>());		//Se inserta un nuevo rio
	}
}

void Cuenca::insertar_pantano(const string& r, const string& p, const int& p1, const int& p2) {

}