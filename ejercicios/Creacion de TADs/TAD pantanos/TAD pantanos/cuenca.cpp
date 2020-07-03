#include "cuenca.h"
#include "DiccionarioHash.h"
#include <string>

using namespace std;

Cuenca::Cuenca() {};

void Cuenca::insertar_rio(const string& r) {
	if (_rios.contiene(r)) {
		throw ERioDuplicado{};
	}
	else {
		_rios.inserta(r, DiccionarioHash<string, info_pantano>());												//Se inserta un nuevo rio
	}
}

void Cuenca::insertar_pantano(const string& r, const string& p, const float& n1, const float& n2) {				//Esta bien
	if (_rios.contiene(r)) {
		DiccionarioHash<string, infoPantano>::Iterator it = _rios.busca(r);	//Obtenemos el rio en el que queremos meter el pantano
		if (!it.valor().contiene(p)) {
			if (n2 > n1) it.valor().inserta(p, info_pantano(n1, n1)); //n2 = n1
			it.valor().inserta(p, info_pantano(n1, n2));
		}
		else {
			throw EPantanoDuplicado {};
		}
	}
	else throw ERioNoExiste {};
}

void Cuenca::embalsar(string r, string p, float n) {
	if (_rios.contiene(r)) {
		DiccionarioHash<string, infoPantano>::Iterator it = _rios.busca(r);
		if (it.valor().contiene(p)) {
			if (it.valor().busca(p).valor().cactual() + n > it.valor().busca(p).valor().cmax()) it.valor().busca(p).valor().ponVol(it.valor().busca(p).valor().cmax());
			else {
				it.valor().busca(p).valor().ponVol(it.valor().busca(p).valor().cactual() + n);
			}
		}
		else {

		}
	}
	else throw ERioNoExiste{};
	
}

float Cuenca::embalsado_pantano(const string& r, const string& p) const{		//Equivalente a un pon a 0
	if (_rios.contiene(r)) {
		DiccionarioHash<string, infoPantano>::ConstIterator it = _rios.cbusca(r);
		if (it.valor().contiene(p)) {
			return it.valor().cbusca(p).valor().cactual();
		}
		else {

		}
	}
	else throw ERioNoExiste{};
}

float Cuenca::embalsado_cuenca(string r) const{
	float agua = 0;
	if (_rios.contiene(r)) {
		
		DiccionarioHash<string, info_pantano>::ConstIterator it = _rios.cbusca(r).valor().cbegin();
		
		while (it != _rios.cbusca(r).valor().cend()) {
			agua += it.valor().cactual();
			it.next();
		}
	}
	else throw ERioNoExiste{};
	return agua;
}
