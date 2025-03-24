//en este programa se introduciran una secuencia de
//numeros, y luego se hara el promedio redondando hasta
//2 decimas
//input: una secuencia de numeros
//output: el promedio con 2 decimas redondeando hacia arriba
#include<iostream>
using namespace std;
int main () {
    int i= 0;
    double n;
    double x= 0.0;

    while (cin >> n) {
        x = x + n;
        ++i;
    }
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << x / i <<endl;
}
