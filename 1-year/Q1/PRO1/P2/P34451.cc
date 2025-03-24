//el programa leera un numero integro positivo,
//introducimos una secuencia de enteros, y el programa
//te dira cuantos numeros enteros son multiplos del primer
//numero introducido
//input: un numero n>0 y una secuencia de enteros
//output: los numeros de la secuencia multiplos de n
#include<iostream>

using namespace std;
int main () {
    int n;
    int a;
    int cont= 0;
    cin >> n;
    while (cin >> a){
        if(a % n == 0) {cont= cont +1; }
                    }

    cout << cont <<endl;
}
