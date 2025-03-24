//con una funcion ya dada hay que
//decir la distancia entre el punto x
//y el punto y
//input: dos numeros reales
#include <iostream>
#include <cmath>
using namespace std;

double dist_or(double x,double y) {
  double distancia = sqrt ((x * x) + (y * y));
  return distancia;
}

int main() {
  double x,y;
  while (cin >> x >> y) cout << dist_or(x,y) << endl;
}
