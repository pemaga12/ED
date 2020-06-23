#include <iostream>
#include <stdio.h>

using namespace std;

// P: 0<=n<=longitud(v) && forall k:0<=k<n:v[k]>=0
// para evitar problemas con los negativos
int parImpar(int v[], int n) {
 
    int p=0, x=0, npares=0;
    /* 
        Invariante:
            0<= x<= n
            && p = # i,j : 0 <=i <j <x: v[i] % 2=0 && v[j] % 2=1 
            && npares = # z:0<= z <n : v[z] % 2 =0
    */

    while (x<n) {
        if ((v[x]%2)==0) { 
            npares ++;
        } else {
            p += npares;
        }
        x++;
    }
    return p;
}
//Postcondicion:
//p = # i,j : 0 <=i <j <n: v[i] % 2=0 && v[j] % 2=1
