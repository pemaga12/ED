#pragma once
#ifndef GUINDOWS_H
#define GUIDOWS_H

#include<string>
#include "DiccionarioHash.h"
#include "hash.h"
#include "lista.h"

using namespace std;

class EColaVacia{};
class EProcesoNoExiste{};

typedef Lista<unsigned int>::Iterator iteradorPos;

class Usuario {
private:

public:
	string _nombreUsuario;
	string _descripcion;
	string _ruta;
	iteradorPos _queueReference;
	

	Usuario(string nombreusuario, string descripcion, string ruta, iteradorPos it) : 
		_nombreUsuario(nombreusuario), _descripcion(descripcion), _ruta(ruta), _queueReference(it){}
	
};

class ProcessManager {
private:

	DiccionarioHash<unsigned int, Usuario> _processList;
	Lista<unsigned int> _processQueue;
	int _numProcesos;
	int _pidCount;										//Variable que uso para calcular el id de los procesos. Nunca ningun proceso tendrá el mismo id

public:
	

	ProcessManager();

	int an_proceso(const string& u, const string& d, const string& r);

	int pid_siguiente() const;

	void ejecuta();

	Usuario detalles(const int& pid) const;

	void termina(const int& pid);

	int numProcesos() const;

};

#endif