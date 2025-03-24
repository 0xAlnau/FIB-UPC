//dada una secuencia de palabras, el programa dira
//cual es la primera secuencia que tiene el orden
//de palabra creciendo lexicograficamente.
//input: un nombre n, que indica la cantidad de palabras
//en una secuencia
//output: indica las palabras que van creciendo
#include<iostream>
using namespace std;
int main() {
    int n = -1;
    int contador = 0;
    bool salir = false, creciente = true;
    string palabra, palabraantes;
    while (not salir and cin >> n) {
        creciente = true;
        cin >> palabraantes;
        for (int i =1; i < n; ++i){
            cin >> palabra;
            if (palabra > palabraantes) { }
            else if (palabra < palabraantes) { creciente = false;}
            palabraantes = palabra;
        }

        ++contador;
    }
    if (creciente and n != -1) {cout << "The last line in increasing order is " << contador << "." <<endl;}
    else if (n == -1) { cout << "There is no line in increasing order." <<endl;}
    else { cout << "There is no line in increasing order." <<endl;}
}
