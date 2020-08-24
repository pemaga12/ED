// PON AQUÍ TU NOMBRE Y APELLIDOS, ASÍ COMO EL NÚMERO DE TU DOCUMENTO IDENTIFICATIVO
// NOMBRE:
// APELLIDOS: 
// DNI / NIE:


#include "GestionDeMatriculas.h"

/* Indicar justificadamente la complejidad de la operación
	O(1) solo se hace una asignacion
*/
GestionDeMatriculas::GestionDeMatriculas() {
	// IMPLEMENTAR
}


/* Indicar justificadamente la complejidad de la operación
	El coste es O(1) ya que solo se realizan asignaciones
*/
void GestionDeMatriculas::registra_curso(const tCurso& curso, unsigned int plazas) {
	//1. compruena si el curso existe
	if (cursos.contiene(curso)) throw ECursoYaExiste();
	//2. Ceramos el curso
	Curso c(plazas);
	//3. lo insertamos en la lista de cursos
	cursos.inserta(curso, c);
}


/* Indicar justificadamente la complejidad de la operación
	 El coste es O(1) ya que solo se realizan asignaciones
*/
void GestionDeMatriculas::registra_estudiante(const tEstudiante& estudiante) {
	// IMPLEMENTAR
	if (estudiantes.contiene(estudiante)) throw EEstudianteYaRegistrado();
	//2. creamos una estructura de estudiante para añadirlo
	DatosEstudiante e(estudiante, 0);				//La matricula = 0 simboliza que no esta apuntado a ninguna asignatura
	//3. lo añadimos al diccionario de estudiantes
	estudiantes.inserta(estudiante, e);
}


/* Indicar justificadamente la complejidad de la operación
O(1)
*/
void GestionDeMatriculas::registra_solicitud(const tEstudiante& estudiante, const tCurso& curso) {
	// IMPLEMENTAR
	//1. comprueba si existe el estudiante y el curso
	if (!estudiantes.contiene(estudiante) || !cursos.contiene(curso)) throw ESolicitud();
	//2. Comprobamos si hay una solicitud previa del estudiante
	if (colaSolicitudes.contiene(estudiante)) {
		//2.1 Si el estudiante está matriculado en curso se borra la solicitud anterior de la cola de solicitudes
		if (cursos.busca(curso).valor().matriculasAlumnos.contiene(estudiante)) cancela_solicitud(estudiante);
	}
	else {
		//Esto es en caso de que el estudiante no se encuentre en ningun curso o que el curso que pida no sea el mismo en el que está
		colaSolicitudes.inserta(estudiante, curso);
	}

}


/* Indicar justificadamente la complejidad de la operación
 O(1)
*/
void GestionDeMatriculas::cancela_solicitud(const tEstudiante& estudiante) {
	// IMPLEMENTAR
	if (!estudiantes.contiene(estudiante)) throw EEstudianteNoExiste();
	if (colaSolicitudes.contiene(estudiante)) {
		colaSolicitudes.borra(estudiante);
	}
}

/* Indicar justificadamente la complejidad de la operación

*/
ResultadoSolicitud GestionDeMatriculas::atiende_solicitud() {
	// IMPLEMENTAR
	//Obtenemos el primer elemento de la cola
	
	DiccionarioHash<tEstudiante, tCurso>::Iterator it = colaSolicitudes.begin();
	ResultadoSolicitud r(it.clave(), it.valor(), true);
	//Comprobamos si el curso que se quiere cursar tiene plazas libres
	int capacidadMaximaCurso = cursos.busca(it.valor()).valor().capacidadMaxima;
	int capacidadActualCurso = cursos.busca(it.valor()).valor().capacidadActual;
	
	if (capacidadMaximaCurso > capacidadActualCurso) {
		//Procedemos a matricular al alumno
		//Comprobamos si está en otro curso
		DiccionarioHash<tCurso, Curso>::Iterator itCurso = cursos.begin();
		while (!itCurso.valor().matriculasAlumnos.contiene(it.clave()) || itCurso != cursos.end()) itCurso.next();
		//En caso de que lo haya encontrado
		if (itCurso != cursos.end()) {
			//Lo borramos del curso en el que estaba y dejamos una plaza más libre
			itCurso.valor().matriculasAlumnos.borra(it.clave());
			itCurso.valor().capacidadActual--;
		}
		//Ahora lo metemos en la nueva asignatura
		estudiantes.busca(it.clave()).valor().num_matricula = cursos.busca(it.valor()).valor().contadorMatriculas;
		cursos.busca(it.valor()).valor().contadorMatriculas++;			//Lo aumentamos para el proximo estudiante
		cursos.busca(it.valor()).valor().matriculasAlumnos.inserta(it.valor(), estudiantes.busca(it.clave()));

	}
	else r.aceptada = false;

	//Elimina la solicitud de la cola
	colaSolicitudes.borra(it.clave());
	return r;
}

/* Indicar justificadamente la complejidad de la operación
 O(n) ya que se recorre la lista de estudiantes
*/
Lista<DatosEstudiante> GestionDeMatriculas::estudiantes_en_curso(const tCurso& curso) const {
	// IMPLEMENTAR
	if (!cursos.contiene(curso)) throw ECursoNoExiste();
	//Buscamos el curso
	DiccionarioHash<tCurso, Curso>::ConstIterator it = cursos.cbusca(curso);
	//Creamos un iterador para recorrer la lista de alumnos del curso
	Diccionario<tEstudiante, DiccionarioHash<tEstudiante, DatosEstudiante>::Iterator>::ConstIterator itCurso = it.valor().matriculasAlumnos.cbegin();
	Lista<DatosEstudiante> alumnos;
	while (itCurso != it.valor().matriculasAlumnos.cend()) {
		alumnos.pon_ppio(itCurso.valor().valor());
	}
	return alumnos;
}


