#include <string>
#include "hospital.h"

using namespace std;

Gestion::Gestion()
{
}

void Gestion::an_paciente(unsigned int c, string n, int e, string s, string g){
	//Comprobamos si el paciente existe
	if (_pacientes.contiene(c)) throw EPacienteExiste();

	Lista<unsigned int>::Iterator it = _cola_g.end();

	//Añadimos el paciente a la cola correspondiente
	if (g == "grave") { 
		_cola_g.pon_ppio(c);
		Lista<unsigned int>::Iterator it = _cola_g.begin();
	}
	else if (g == "leve") {
		_cola_l.pon_ppio(c);
		Lista<unsigned int>::Iterator it = _cola_l.begin();
	}
	else if (g == "normal") {
		_cola_n.pon_ppio(c);
		Lista<unsigned int>::Iterator it = _cola_n.begin();
	}
	

	//Añadimos el paciente a el diccionario con el resto de pacientes
	Info_paciente info(n, e, s, g, it);

	_pacientes.inserta(c, info);
	_gente++;
	
}

void Gestion::info_paciente(unsigned int c, string n, int e, string s){
	if (!_pacientes.contiene(c)) throw EPacienteNoExiste();
	
	//Cambia los datos del paciente
	//1. Obtenemos un iterador del paciente
	DiccionarioHash<unsigned int, Info_paciente>::Iterator it = _pacientes.busca(c);
	//2. Modificamos los datos
	it.valor()._edad = e;
	it.valor()._sintomas = s;
	it.valor()._nombre = n;

}

void Gestion::siguiente(unsigned int c, string g){
	if (_gente == 0) throw ENoHayPacientes();
	
	if (_cola_g.longitud() > 0) {
		_codigo = _cola_g.primero();
		_gravedad = "grave";
		_cola_g.quita_ppio();
	}
	else if (_cola_n.longitud() > 0) {
		_codigo = _cola_n.primero();
		_gravedad = "normal";
		_cola_n.quita_ppio();
	}
	else {
		_codigo = _cola_l.primero();
		_gravedad = "leve";
		_cola_l.quita_ppio();
	}
	DiccionarioHash<unsigned int, Info_paciente>::Iterator it = _pacientes.busca(c);
	it.valor()._it_cola = _cola_l.end();			//Como ya no está en ninguna cola le ponemos el iterador apuntando a fuera de una cola (la que sea)

	_gente--;
}

bool Gestion::hay_pacientes() const
{
	if (_gente > 0) return true;
	else return false;
}

void Gestion::elimina(unsigned int c){
	if (!_pacientes.contiene(c)) throw EPacienteExiste();
	
	DiccionarioHash<unsigned int, Info_paciente>::Iterator it = _pacientes.busca(c);
	if (it.valor()._it_cola != _cola_l.end()) {
		if (it.valor()._nivel_urgencia == "grave") {
			_cola_g.eliminar(it.valor()._it_cola);
		}
		else if (it.valor()._nivel_urgencia == "normal") {
			_cola_n.eliminar(it.valor()._it_cola);
		}
		else {
			_cola_l.eliminar(it.valor()._it_cola);
		}
		_gente--;
	}
	_pacientes.borra(c);
}


