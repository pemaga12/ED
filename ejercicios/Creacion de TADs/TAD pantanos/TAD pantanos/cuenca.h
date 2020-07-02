#include "DiccionarioHash.h"
#include "hash.h"
using namespace std;

class ERioDuplicado{};
class ERioNoExiste{};
class EPantanoDuplicado{};
class EPantanoNoExiste{};

#ifndef CUENCA_H
#define CUENCA_H

class info_pantano {
private:
	float _cMax;
	float _cActual;

public:
	info_pantano(float cMax = 0, float cActual = 0) : _cMax(cMax), _cActual(cActual) {};
	
	
	float cmax() const { return _cMax; }
	float cactual() const { return _cActual; }

	void ponVol(float vol) {
		_cActual = vol;
	}
};

class Cuenca {
private:
	
	using infoPantano = DiccionarioHash<string, info_pantano>;				//Informacion de los pantanos
	DiccionarioHash<string, DiccionarioHash<string, info_pantano>> _rios;								//Información de cada cuenca
public:

	Cuenca();

	

	void insertar_rio(const string& r) ;

	void insertar_pantano(const string& r, const string& p, const float& n1, const float& n2);

	void embalsar(string r, string p, float n);

	float embalsado_pantano(const string& r,const string& p) const;

	float embalsado_cuenca(string r) const;

	void trasbasar(string r1, string p1, string r2, string p2, float n);


};

#endif // !CUENCA_H
