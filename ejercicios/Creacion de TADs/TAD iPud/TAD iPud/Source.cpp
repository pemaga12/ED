#include <iostream>
#include <string>
#include "iPud.h"

using namespace std;

int main() {
	IPud ipod;
	ipod.addSong("la tartana", "bad bunny", 3);
	ipod.addSong("la tartona", "bad bunny", 3);
	ipod.addSong("la tartena", "bad bunny", 3);
	ipod.addToPlaylist("la tartana");
	ipod.addToPlaylist("la tartona");
	ipod.addToPlaylist("la tartena");
	ipod.deleteSong("la tartana");
	Lista<string> playlist = ipod.playlist();

	Lista<string>::Iterator plIt = playlist.begin();
	while (plIt != playlist.end()) {
		cout << plIt.elem() << endl;
		plIt.next();
	}


	DiccionarioHash<string, SongInfo>::Iterator it = ipod.canciones().busca("la tartana");
	if (it != ipod.canciones().end())
		cout << "chi";
	
	system("pause");
	return 0;
}