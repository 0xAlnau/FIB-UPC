#include <typeinfo>
#include <iostream>
using namespace std;

struct Rational {
  int num, den;
};
//esta funcion calcula el racional normalizado
//dados un numerador y un denominador
//Pre: dos enteros
//Post: un struct de enteros
Rational rational(int n, int d) {
  Rational r;
  if (n == 0) {
    r.num = 0;
    r.den = 1;
  }
  else {
      int a = n, b = d;
    while (b != 0) { //mcd
      int res = a % b;
      a = b;
      b = res;
    }
    r.num = n / a;
    r.den = d / a;
    if (r.den < 0) {r.den = -1 * r.den;}
    if (((n < 0 and d > 0) or (n > 0 and d < 0)) and r.num > 0) {r.num = -1 * r.num;}
  }
  return r;
}

int main(){
  int num, den;
  while (cin >> num >> den) {
    Rational r = rational(num, den);
    cout << r.num << " " << r.den << endl;
  }
}
