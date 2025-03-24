//en este programa el usuario introducira un numero real
//y el programa dara como salida el redondeo hacia abajo,
//hacia arriba, y el numero entero mas cercano si este tiene
//decimales infinitos
//input: numero real superior o igual a 0
//output: tres numeros enteros, redondeo hacia arria, abajo y
//si tiene infinitos decimales, el entero mas cercano

#include<iostream>
using namespace std;
int main () {
    double a;
    cin >> a;

    double w= (a / 10);
    double b= a + w + 0.5 - int(w);

    double c= a + 0.5;
    cout << int(a) << " " << int(b) << " " <<int(c) <<endl;

}
