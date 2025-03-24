#include <iostream>
#include <vector>
using namespace std;
vector<int> read_vector() {
    int size;
    cin >> size;
    vector<int> v (size);
    for (int i = 0; i < size; ++i) {
        cin >> v[i];
    }
    return v;
}
//esta función se encargara de decir cuantos elementos en
//comun tienen dos vectores en orden creciente cada uno
//Pre: dos vectores de diferentes tamaños pero en orden creciente
//Post: un entero con las veces que un elemento coincide con otro
int common_elements(const vector<int>& X, const vector<int>& Y) {
    int sizex = X.size();
    int sizey = Y.size();
    int contador = 0;
    int a = 0, b = 0;
    while (a < sizex and  b < sizey) {
        if (X[a] > Y[b]) { ++b; }
        else if (X[a] < Y[b]) { ++a; }
        else {
            ++a;
            ++b;
            ++contador;
        }
    }
    return contador;
}

