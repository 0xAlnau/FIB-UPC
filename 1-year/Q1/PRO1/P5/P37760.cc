//el programa leera una secuencia de angulos
//y dira su coseno y seno
//input: numeros reales que representen angulos
//output: el seno y coseno del angulo, con 6
//digitos de decimal
#include<iostream>
#include<cmath>
using namespace std;
double radiantes (double x) {
    double radiantes = (x * M_PI) / 180;
    return radiantes;
}
double seno (double x) {
    double anguradiantes = radiantes (x);
    double seno = sin (anguradiantes);
    return seno;
}
double coseno (double x) {
    double anguradiantes = radiantes (x);
    double coseno = cos (anguradiantes);
    return coseno;
}
int main () {
    double angulo;
    cout.setf(ios::fixed);
    cout.precision (6);
    while (cin >> angulo) {
        cout << seno (angulo) << " " << coseno (angulo) <<endl;
    }
}
