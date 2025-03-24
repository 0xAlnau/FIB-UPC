//el programa leera secuencias no vacias de numeros reales,
//dira el numero maximo, el  minimo y el promedio de todos
//input: un numero real n que nos indica cuantos elementos tenemos
//que tratar. Los numeros a tratar son numeros reales.
//output: el maximo, minimo y promedio de los numeros, con 4 decimales siempre
#include<iostream>
using namespace std;
int main () {
int ns;
int ne;
double max;
double min;
double prom = 0;
double real;
cin >> ns;

for (int i= 0; i < ns; ++i){
    prom = 0;
    cin >> ne;

    cin >> real;
    max = real;
    min = real;
    prom = prom + real;
    for (int j = 1; j < ne; ++j) {
        cin >> real;
        prom = prom + real;
        if (real >= max) {
            max = real;
        }
        else if (real <= min){
            min = real;
        }
    }

    cout.setf(ios::fixed);
    cout.precision(4);
    cout << min << " " << max << " " << prom / ne <<endl;
}

}
