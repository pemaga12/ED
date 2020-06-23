#include <iostream>
#include <stdio.h>

using namespace std;

//Version no final que calcula la suma
long long int suma(long long int isbn, int& ndigitos) {
    int s,m;
    if (isbn<=9) {
        ndigitos=1; 
        s=isbn;
    } else {
        s = suma(isbn/10,ndigitos);
        if (ndigitos%2==1) {
            s=s+isbn%10*3;
        } else {
            s=s+isbn%10;
        }
        ndigitos=ndigitos+1;
    }
    return s;
}

//Version final que calcula la suma
//suma1 lleva la suma de los digitos desde el menos significativo
//suma2 lleva la suma de los digitos desde el a
long long int sumaFinal(long long isbn,int ndigitos,int suma1,int suma2) { 
    int res;
    if (isbn<=9) {
        if  (ndigitos%2==0) { 
            res = suma1*3 + suma2 + isbn;
        } else {
            res=suma2*3 + suma1 + isbn;
        }
    } else {
        if (ndigitos%2==0) {
            res = sumaFinal(isbn/10,ndigitos+1,suma1,suma2+isbn%10);
        } else { 
            res = sumaFinal(isbn/10,ndigitos+1,suma1+isbn%10,suma2);             
        }        
    }
    return res;
}

//Version final que calcula el digito
long long int digito(long long isbn,int ndigitos,int suma1,int suma2) { 
    int res;
    if (isbn==0) {
        if (ndigitos%2==1) { 
            res = suma1*3 + suma2;       
        } else { 
            res=suma2*3 + suma1;
            
        }
        res = (10-res%10)%10;
    } else {
        if (ndigitos%2==0) {
            res = digito(isbn/10,ndigitos+1,suma1,suma2+isbn%10);            
        } else { 
            res = digito(isbn/10,ndigitos+1,suma1+isbn%10,suma2);             
        }
    }
    return res;
}