#include <iostream>
#include <string>
#include "cola.h"


bool resuelveCaso() {
	
	int aux, n, i;
	std::cin >> n >> i;

	if (n == 0) return false;

	Cola<int> cola;
	for (size_t i = 0; i < n; ++i){
		std::cin >> aux;
		cola.pon(aux);
	} 
		
	cola.llevarAlPrincipio(i);
	while (!cola.esVacia()) {
		int x = cola.primero();
		cola.quita();
		std::cout << x << " ";
	}
	std::cout << "\n";

	return true;
}

int main() {
	while (resuelveCaso());
	return 0;
}
