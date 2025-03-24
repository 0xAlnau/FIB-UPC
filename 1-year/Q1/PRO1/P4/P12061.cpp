//el programa leera una secuencia de palabras, y dira el
//numero de palabras entre "beggining" y "end". Si algo esta mal
//puesto o falta "begging" o "end" se ha de decir
//input: secuencia de palabras con un "beggining" y un "end"
//output: numero de palabras entre "beggining" y "end", lo contrario
//imprimir "wrong sequence"
#include<iostream>
using namespace std;
int main () {
    string palabra;
    int contador = 0, contadorend = 0;
    bool wrong = false, out = false;
    while (not out and cin >> palabra) {
        if (palabra == "beginning") {out = true;}
        else if (palabra == "end") { out = true; wrong = true;}
    }

    while (not wrong and palabra != "end" and cin >> palabra) {
        if (palabra == "end") { ++contadorend; }
        ++contador;

    }

    if (not wrong and contadorend != 0) { cout << contador -1 <<endl; }
    else { cout << "wrong sequence" << endl; }
}
