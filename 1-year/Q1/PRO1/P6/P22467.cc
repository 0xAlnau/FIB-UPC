#include <iostream>
using namespace std;

//esta funcion calculara la suma de digitos de un
//numero dado:
//Precondici贸n: un numero entero
//Postcondici贸n: un entero que es la suma
//de digitos del anterior.
int suma_digitos (int numero) {
    if (numero < 10) { return numero;}
    else {
        return (numero % 10) + suma_digitos(numero / 10);
    }
}
//esta funcion dira si un numero es primo o no
//Precondici贸n: un numero entero
//Postcondici贸n: un booleanono.
bool primo_or_not(int numero, int divisor) {
    if (numero <= 1) { return false;}
    else if (divisor * divisor > numero) { return true;}
    else if (numero % divisor == 0) {return false;}
    else {
        return primo_or_not(numero, divisor + 1);
    }
}

bool is_perfect_prime(int n) {
    if (primo_or_not(n, 2)) {
        if (suma_digitos(n) / 10 == 0 and primo_or_not(suma_digitos(n), 2)) {
            return true;
        }
        else {
            return is_perfect_prime(suma_digitos(n));
        }
    }
    else { return false; }

}
int main() {
    int n;
    while (cin >> n) {
        if (is_perfect_prime(n)) {cout << "true" <<endl;}
        else {cout << "false" <<endl;}

    }
}
