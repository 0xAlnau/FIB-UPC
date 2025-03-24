//este programa leera secuencias de numeros enteros
//y en otra linia dara el orden inverso de esa secuencias
//input: un numero natural n seguido de  n enteros
//output: las secuencias con orden inverso
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    while (cin >> n) {
        if (n == 0) {cout <<endl;}
        else {
            vector <int> v(n);
            for (int i = 0; i < n; ++i) {
                cin >> v [i];
            }

            for (int j = 0; j < n / 2; ++j) {
                int aux = v[j];
                v[j] = v[n - 1 - j];
                v[n - 1 - j] = aux;
            }

            for (int k = 0; k < n - 1; ++k) {
                cout << v[k] << " ";
            }
            cout << v[n -1] <<endl;
            }
    }

}
