//el programa leera numeros naturales y dira
//cual es su raiz cuadrado y su cuadrado
//input: secuencia de numeros naturales
//output: la raiz cuadrada con seis digitos decimales y su cuadrado
#include<iostream>
#include<cmath>
using namespace std;
double raizcuadrada (int x) {
    double raizcuadrada = sqrt(x);
    return raizcuadrada;
}
int cuadrado (int y) {
    int cuadrado = y * y;
    return cuadrado;
}
int main () {
    int n;
    while (cin >> n) {
    cout << cuadrado (n) << " ";
    cout.setf(ios::fixed);
    cout.precision (6);
    cout << raizcuadrada (n) <<endl;
    cout.precision (0);
    }

}
