#include <iostream>
#include <string>
#include "guidows.h"

using namespace std;

int main() {
	ProcessManager m;
	
	m.an_proceso("pedro", "hace lo que quiere", "/user/desktop/hola.exe");
	m.an_proceso("pedro", "hace lo que quiere", "/user/desktop/adios.exe");
}