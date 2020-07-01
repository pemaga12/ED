#pragma once
#ifndef __HOTELES_H
#define __HOTELES_H

#include <fstream>
#include <cstddef>
#include "diccionario.h"
#include "lista.h"
using namespace std;


template<class tCliente, class tHotel>
class Hoteles{
private:
	Diccionario<tHotel, Lista<tCliente>> hotel;				//Lista con todos los huespedes de un hotel
	
	using infoCliente = Diccionario<tHotel, Lista<tCliente>::Iterator>;
	Diccionario<tCliente, infoCliente> huespedes;				//Los clientes aparecen ordenados alfabéticamente

public:
	static void aloja(tCliente c, tHotel h) {
		if (!huespedes->contiene(c)) throw hNoExiste();
		else {

		}
	}

	static void desaloja(tCliente c) {

	}

	static tHotel alojamiento(tCliente c) {

	}

	static Lista<tHotel> listadoHoteles() {

	}

	static Lista<tCliente> huespedes(tCliente h) {

	}
};

#endif