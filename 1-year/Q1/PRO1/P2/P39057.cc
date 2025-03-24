//el programa calculara las areas de los
//rectangulos i circulos indicados por el
//usuario
//input: un numero n que nos indica el numero
//de areas a tratar, si la palabra es "rectangulo"
//hace falta escribir dos numeros naturales despues de esta
//si la palabra es "circulo" solo hace falta escribir el radio,
//tambien numero natural, ha de acabar con putnos decimales.

#include<iostream>
#include<cmath>
using namespace std;
int main() {
   string s;
   double x;
   double y;
   int n;
   cin >> n;
   for (int i= n; i > 0; --i){
       cin >> s;

       if (s == "rectangle") {
           cin >> x;
           cin >> y;
           double a= x * y;
           cout.setf(ios::fixed);
           cout.precision(6);
           cout << a <<endl;
    }
       else if (s == "circle") {
           cin >> x;
           double a= M_PI * (x * x);
           cout.setf(ios::fixed);
           cout.precision(6);
           cout << a <<endl;

   }
   }


}
