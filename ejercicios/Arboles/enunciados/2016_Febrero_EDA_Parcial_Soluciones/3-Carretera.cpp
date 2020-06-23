#include <iostream>
#include <stdio.h>

using namespace std;

const int N=5;

struct Celda{
    int fila;
    int columna;
};

bool esValida(float lab[N][N], float hmax, 
              Celda ant, Celda c, int n, const bool marcas[N][N]) {
    // esValida si no esta fuera, el desnivel no supera hmax, y no estaba amrcada
    return c.fila >= 0 && c.fila < n 
        && c.columna >= 0 && c.columna < n 
        && abs(lab[ant.fila][ant.columna]-lab[c.fila][c.columna]) <= hmax 
        && ! marcas[c.fila][c.columna];                                                                                                                                                                        
}

bool esSolucion(Celda pos, Celda dest){
    // esSolucion si llega al destino
    return pos.fila == dest.fila 
        && pos.columna == dest.columna;
}

Celda sigDireccion(int dir, Celda pos){
    // 'pos' es copia, y modificarla no cambia el original
    //   usar Celda &pos causaria errores (por modificar el original)
    switch (dir) {
        case 0: pos.columna ++; break;
        case 1: pos.fila ++; break;
        case 2: pos.columna --; break;
        case 3: pos.fila --; break;
        default: break;
    }
    return pos;
}

/**
 * llamar con
 * - lab: alturas
 * - dest: destino
 * - solucion[0]: origen
 * - k: 1 
 * - n: ancho y alto de lab, marcas
 * - marcas: a false, excepto en casilla origen
 * - mejorlong: a INT_MAX
 */
void carretera(float lab[N][N], Celda dest, 
               float hmax, Celda solucion[], int k, int n, 
               bool marcas[N][N], Celda mejorSol[],int &mejorLong) {
    for (int dir=0; dir < 4; dir ++){
        solucion[k] = sigDireccion(dir, solucion[k-1]); 
        if(esValida(lab, hmax, solucion[k-1], solucion[k], n, marcas)) {
            if (esSolucion(solucion[k],dest)) {
                // es solucion; si mejora, me la quedo; y si no, la descarto
                if (k < mejorLong) {  
                    // nueva "mejor solucion"
                    for (int i=0;i<n;i++) mejorSol[i]=solucion[i];
                    mejorLong=k;
                }
            } else {
                // no es solucion, pero puede todavia formar parte de una
                int longEstimada = k
                    + abs(dest.fila-solucion[k].fila)
                    + abs(dest.columna-solucion[k].columna);
                // longEstimada = coste en el caso mejor
                if (longEstimada<mejorLong){
                    // y si es posible mejorar, intento profundizar (este if)
                    marcas[solucion[k].fila][solucion[k].columna] = true; 
                    carretera(lab, dest, hmax, solucion, k+1, n, 
                              marcas, mejorSol, mejorLong);
                    marcas[solucion[k].fila][solucion[k].columna] = false;     
                }
            }
        }
    }
}
