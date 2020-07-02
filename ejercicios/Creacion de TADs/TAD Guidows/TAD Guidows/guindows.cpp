#include "guidows.h"
#include <string>

using namespace std;

ProcessManager::ProcessManager() : _numProcesos(0), _pidCount(0) {}

int ProcessManager::an_proceso(const string& u, const string& d, const string& r){
	//Generamos el id del proceso
	int pid = _pidCount;
	_pidCount++;			//Aumentamos el PID para el proximo proceso que se añada

	//Añadimos el proceso a la cola de procesos
	
	_processQueue.pon_final(pid);
	_numProcesos++;

	Lista<unsigned int>::Iterator it = _processQueue.begin();
	while (it.elem() != pid) it.next();
	
	//Insertamos el proceso en la lista de procesos
	Usuario user(u, d, r, it);
	_processList.inserta(pid, user);
	

	return pid;
}
int ProcessManager::pid_siguiente() const
{
	if (_processQueue.esVacia()) throw EColaVacia();
	
	return _processQueue.primero();
}

void ProcessManager::ejecuta(){
	if (!_processQueue.esVacia()) {
		//obtenemos el proceso que se ejecutará: _processQueue.primero();
		//lo borramos de la lista de procesos
		_processList.borra(_processQueue.primero());
		//lo borramos de la cola
		_processQueue.quita_ppio();
		//restamos un elemento al contador de procesos en cola
		_numProcesos--;
	}
}
Usuario ProcessManager::detalles(const int& pid) const {
	if (!_processList.contiene(pid)) throw EProcesoNoExiste();

	//Buscamos el proceso en el Diccionario
	DiccionarioHash<unsigned int, Usuario>::ConstIterator it = _processList.cbusca(pid);
	//creamos una variable del tipo usuario para almacenar la informacion del usuario
	return it.valor();
}
void ProcessManager::termina(const int& pid){
	//comprobamos si el proceso existe
	if (_processList.contiene(pid)) {
		DiccionarioHash<unsigned int, Usuario>::Iterator it = _processList.busca(pid);
		//El proceso debe existir en la cola
		_processQueue.eliminar(_processList.busca(pid).valor()._queueReference);
		//Lo borramos de la lista de procesos
		_processList.borra(pid);
		_numProcesos--;
	}
}
int ProcessManager::numProcesos() const
{
	return _numProcesos;
}
;

