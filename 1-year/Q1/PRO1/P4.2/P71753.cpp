//programa leera secuencias, dira segun el numero de
//elementos que quiera el usuario dara el maximo de
//esa secuencias
//input: numero enteros y varias secuencias que empieza
//por un numero que indica cuantos elementos habra
//output: el maximo de cada secuencia
#include <iostream>
using namespace std;
int main () {
    int ne, elemento;
    while(cin >> ne) {
        int max = 0;
        for(int i = 0; i < ne; ++i) {
            cin >>elemento;
            if (max == 0) {max = elemento;}
            if (elemento >= max) { max = elemento; }

        }
        cout << max <<endl;
    }
}
