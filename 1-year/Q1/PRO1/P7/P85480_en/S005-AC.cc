#include<iostream>
#include<vector>
using namespace std;

vector<int> read_in(int size) {
    vector<int> V(size);
    for (int i= 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}
bool primo_or_not (int numero) {
    int divisor = 2;
    bool no_primo = false;
    while (not no_primo and divisor * divisor <= numero) {
                if (numero % divisor != 0) {++divisor;}
                else { no_primo = true; }
            }
            if (not no_primo) {return true;}
            else {return false;}
}
//esta funcion dira si dos elementos de un vector
//suman un numero primo o no
//Pre: un vector y su tamaño
//Post: true si hay dos elementos que sumen un primo, false
//en caso contrario
bool sum_prime (const vector<int> &V, int size) {
    bool prime = false;
    for (int j = 0; not prime and j < size - 1; ++j) {
        int contador = 1;
        while (not prime and contador < size) {
            int numero2 = V[j] + V[contador];
            if (primo_or_not(numero2)) {prime = true;}
            else {++contador;}
        }
    }
    if (prime) {return true;}
    else {return false;}
}
//este programa con la ayuda de una funcion dira si hay
//dos elementos de un vector que sumen un primo
//Input: el tamaño del vector
//output: una linia con "yes" o "no"
int main(){
    int size;
    while (cin >> size) {
        vector<int> V = read_in(size);
        if (sum_prime(V, size)) { cout << "yes" <<endl; }
        else { cout << "no" <<endl; }

    }
}

