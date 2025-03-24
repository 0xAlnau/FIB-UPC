//el programa leera una secuencia de numeros enteros positivos,
//y dira si en la secuencia hay algun pico superior a 3143.
//input: secuencia de enteros positivos con centinela 0, y simpre
//habra como minimo tres enteros aparte del 0
//output: YES si hay pico, de lo contrario
#include<iostream>
using namespace std;
int main () {
    int numero = 9999;
    int numero2 = 9999, numero3 = -1;
    bool found = false;
    cin >> numero3;
    while (not found and numero3 != 0) {
        if (numero2 > numero and numero2 > numero3 and numero2 > 3143) { found = true; }
        numero = numero2; numero2 = numero3;
        cin >> numero3;
    }
    if (found) { cout << "YES" <<endl; }
    else { cout << "NO" <<endl; }
}
