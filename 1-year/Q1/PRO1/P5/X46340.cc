//dados 3 valores de una secuencia, el programa
//dira la suma de el valor maximo y el minimo
#include <iostream>
using namespace std;

int sum_min_max(int x,int y,int z) {
  int max = x, min = x, suma = 0;
  if (y > max) { max = y; }
  else if (y < min) { min = y; }

  if (z > max) { max = z; }
  else if (z < min) { min = z; }

  suma = max + min;
  return suma;
}

int main() {
  int x,y,z;
  while (cin >> x >> y >> z) cout << sum_min_max(x,y,z) << endl;
}
