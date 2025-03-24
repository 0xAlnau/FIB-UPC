//el programa leera un vector no vacio, y dira
//cuantas veces se repite su ultimo numero, contando
//tambien este mismo
//input: un natural con las posiciones del vector, y los numeros
//en cada posicion
//output: una linia con el numero de veces que se repite el ultimo numero
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector <int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    int iguales = 0;
    for (int j = 0; j < n - 1; ++j) {
        if (v[j] == v[n -1]) {++iguales;}
        else{}
    }
    cout <<iguales<<endl;
}

