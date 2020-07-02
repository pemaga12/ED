#pragma once
#ifndef IPUD_H
#define IPUD_H


#include "DiccionarioHash.h"
#include "hash.h"
#include "lista.h"
#include <string>
using namespace std;

class ECancionExiste {};
class ECancionEnPlaylist{};
class ECancionNoExiste{};
class EPlaylistVacia {};

class SongInfo {
public:
	string _artist;
	int _duracion;
	bool _inPLaylist;
	bool _played;
	SongInfo() : _inPLaylist(false), _played(false) {};
};

class IPud{
private:
	DiccionarioHash<string, SongInfo> _songs;
	Lista<string> _playlist;
	Lista<string> _played;
	int _duracion;
public:

	IPud() : _duracion(0) {}

	void addSong(string s, string a, int d) {
		
		if (!_songs.contiene(s)) {
			SongInfo i;
			i._artist = a;
			i._duracion = d;
			_songs.inserta(s, i);
		}
		else throw ECancionExiste{};
	}

	void addToPlaylist(const string& s) {
		if (_songs.contiene(s)) {
			Lista<string>::Iterator playl = _playlist.begin();
			while (playl != _playlist.end()) {					//Bucle para comprobar si la playlist está en la lista
				if (playl.elem() == s) {
					throw ECancionEnPlaylist{};
				}
				playl.next();
			}
			_playlist.pon_final(s);
			_songs.busca(s).valor()._inPLaylist = true;
		}
		else throw ECancionNoExiste{};
	}

	void deleteSong(const string& s) {
		//Habra que borrarla tanto de la playlist como de el diccionario
		if (_songs.contiene(s)) {
			
			//Comprueba si esta en la playlist
			if (_songs.busca(s).valor()._inPLaylist) {
				Lista<string>::Iterator playl = _playlist.begin();
				while (playl.elem() != s) playl.next();					//Bucle para comprobar si la playlist está en la lista

				_playlist.eliminar(playl);
			}
			else if (_songs.busca(s).valor()._played) {

				//Se borra de la lista de reproducidas
				Lista<string>::Iterator playl = _played.begin();
				playl = _played.begin();
				while (playl.elem() != s) playl.next();				//Bucle para comprobar si la playlist está en la lista

				_played.eliminar(playl);
			}
				
			
			//borra la cancion de el diccionario
			_songs.borra(s);
		}
		else throw ECancionNoExiste{};

	}
	/*
	La primera canción de la lista de reproducción abandona la lista de reproducción y se registra como reproducida. 
	Si la lista es vacía la acción no tiene efecto.
	*/
	void play() {							//No funciona por el tema de borrar
		if (!_playlist.esVacia()) {
			_played.pon_ppio(_playlist.primero());
			_songs.busca(_playlist.primero()).valor()._played = true;
			_playlist.quita_ppio();			//Eliminamos el primer elemento de la lista
		}
	}

	string current() {						//Funciona
		if (_playlist.esVacia()) throw EPlaylistVacia{};
		return _playlist.primero();
	}

	int totalTime() {						//Funciona
		return _duracion;
	}

	Lista<string> recent(int n) {
		Lista<string>::ConstIterator it = _played.cbegin();
		Lista<string> reproducidas;
		int aux;
		while (it != _played.cend() || aux < n) {
			reproducidas.pon_ppio(it.elem());
			it.next();
		}
		return reproducidas;
	}

	DiccionarioHash<string, SongInfo> canciones() {
		return _songs;
	}

	Lista<string> playlist() {
		return _playlist;
	}

};
#endif
