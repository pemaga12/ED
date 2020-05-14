#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool igualado(stack<char> &p);

bool esEquilibrada(const string& cadena) {
    string aux = cadena;
    stack<char> p;
    bool res = true;

    for (int i = 0; i < aux.length(); i++) {
        if (aux[i] == '(' || aux[i] == '[' || aux[i] == '{') {      //En caso de que el programa detecte que se ha iniciado un parentesis
            p.push(aux[i]);
        }
        if (aux[i] == ')' || aux[i] == ']' || aux[i] == '}') {      //En caso de que el programa detecte que se ha finalizado un parentesis
            p.push(aux[i]);
            res = igualado(p);
        }
    }

    if (res && p.empty()) return true;
    else return false;
}


int main() {
    string cadena;
    while (getline(cin, cadena)) {
        if (esEquilibrada(cadena))
            cout << "EQUILIBRADA" << endl;
        else
            cout << "NO_EQUILIBRADA" << endl;
    }
    return 0;
}


bool igualado(stack<char> &p) {                                  //Comprobación de si se llegan a cerrar los paréntesis
    char ultimo = p.top();
    p.pop();

    if (p.empty()) return false;

    else if (ultimo == ')' && p.top() == '(') {
        p.pop();
    }
    else if (ultimo == '}' && p.top() == '{') {
        p.pop();
    }
    else if (ultimo == ']' && p.top() == '[') {
        p.pop();
    }

    else return false;

    return true;
}