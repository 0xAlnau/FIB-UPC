#include<iostream>
#include<vector>
using namespace std;
vector<int> read_vector (int size){
    vector<int> V(size);
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}
//Esta funcion dara true si la suma de los
//digitos de un vector es igual a un elemento
//del vector, dara false en caso contrario
//Pre: un vector
//Post: un booleano
bool sum_of_the_rest (const vector<int> &V, int size){
    bool found  = false;
    int suma = 0;
    for (int i = 0; i < size; ++i) {
        suma = suma + V[i];
    }
    for (int j = 0; not found and j < size; ++j){
        if (V[j] == suma - V[j]) {
            found = true;
            }
    }

    if (found) {return true;}
    else {return false;}
}
//este programa con la ayuda de una funcion
//dira si un digito de una secuencia de un vector
//es igual a la suma de los otros o no
//Input: un entero con la mida del vector
//Output: una linia con "YES" o "NO"
int main(){
    int size;
    while (cin >> size) {
        vector<int> V = read_vector(size);
        if (sum_of_the_rest(V, size)) {cout << "YES" <<endl;}
        else{ cout << "NO" <<endl;}
    }
}


