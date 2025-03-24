//el programa leera dos numeros, y dira todos
//los otros numeros del mas grande al pequeño
//input: dos numeros enteros
//output: todos los numeros del intervalo
//del mas grande al mas pequeño
#include<iostream>
using namespace std;
int main () {
    int x, y;
    cin >> x >> y;

    if (x > y){
        for (int i= x; i >= y; --i){
            cout << i <<endl;
        }
    }

    else if (y > x){
        for (int i= y; i >= x; --i){
            cout << i <<endl;
        }
    }

    else if (y == x){
        cout << x <<endl;
    }
}
