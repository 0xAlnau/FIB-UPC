//el programa leera el numero de secuencias introducidas
//por el ususario. En cada secuencia se dira cuantas veces
//los despues de un natural ese otro numero es mayor que el previo
//input: un numero n, y n secuencias con numeros naturales con centinela 0
//output: las veces que se cumple la condicion previa
#include<iostream>
using namespace std;
int main () {
    int ns;
    int contador = 0;
    int numero, numero2;
    cin >> ns;
    for (int i = 0; i < ns; ++i) {
        cin >> numero2;
        contador = 0;
        numero = 99999;
        while (numero2 !=0) {
            if (numero < numero2 and numero != numero2) { ++contador;}
            numero = numero2;
            cin >> numero2;
        }
    cout << contador <<endl;
    }

}
