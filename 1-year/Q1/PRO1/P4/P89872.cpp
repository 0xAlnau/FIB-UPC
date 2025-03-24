//el programa leera una secuencia de palabras
//y tendra que decir cual es la segunda palabra
//mas grande por orden alfabetico, y sin contar
//con palabras que se repitan
//input: secuencia de palabras en minuscula, dos
//palabras diferentes siempre
//output: la segunda palabra mas grande alfabeticamente
#include<iostream>
using namespace std;
int main () {
    string palabra, segundo, mayor;
    cin >> palabra;
    mayor = palabra;
    while (cin >> palabra) {
        string temp;
        if (palabra == mayor) { mayor = palabra; }
        else if (palabra == segundo) { segundo = palabra; }

        else if (mayor < palabra) {
            temp = mayor;
            mayor = palabra;
            segundo = temp;

        }
        else if (mayor > palabra) {
            if (palabra > segundo) { segundo = palabra; }
        }

        else if (segundo < palabra) {
            segundo = palabra;
        }

        else if (segundo > palabra) {}

    }

    cout << segundo <<endl;
}
