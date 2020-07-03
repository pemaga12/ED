#pragma once
#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include "DiccionarioHash.h"
#include "hash.h"
#include "lista.h"

using namespace std;


class EPacienteExiste {};
class EPacienteNoExiste {};
class ENoHayPacientes {};

typedef Lista<unsigned int>::Iterator it_usuario;

class Info_paciente {
public:
	string _nombre;
	int _edad;
	string _sintomas;
	string _nivel_urgencia;
	it_usuario _it_cola;

	Info_paciente(string n, int e, string s, string nu, it_usuario it) :
		_nombre(n), _edad(e), _sintomas(s), _nivel_urgencia(nu), _it_cola(it){};
};

class Gestion {
private:
	DiccionarioHash<unsigned int, Info_paciente> _pacientes;
	Lista<unsigned int> _cola_g;
	Lista<unsigned int> _cola_l;
	Lista<unsigned int> _cola_n;
	int _gente;
	unsigned int _codigo;
	string _gravedad;


public:
	Gestion();

	void an_paciente(unsigned int c, string n, int e, string s, string g);

	void info_paciente(unsigned int c, string n, int e, string s);

	void siguiente(unsigned int c, string g);

	bool hay_pacientes() const;

	void elimina(unsigned int c);


};



#endif