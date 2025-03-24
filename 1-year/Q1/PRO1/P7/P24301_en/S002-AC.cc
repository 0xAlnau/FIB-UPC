#include<vector>
#include<iostream>
using namespace std;
vector<int> read_vector(int& size){
    cin >> size;
    vector<int> V(size);
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}
//esta funcion se encargara crear un vector que
//concatene dos vectores de enteros ya llenos
//Pre: dos vectores de enteros y sus tamaños
//Post: el vector concatenado
vector<int> concatenation(const vector<int>& v1, const vector<int>& v2){
    int size = v1.size();
    int size2 = v2.size();
    vector<int> A(size + size2);
    for (int i = 0; i < size + size2; ++i) {
        if (i < size) {
            A[i] = v1[i];
        }
        else {
            A[i] = v2[i - size];
        }
    }
    return A;
}
//este programa imprimira un vector que sea
//la concatenacion de otros dos vectores
//con la ayuda de una funcion
//Output: el vector concatenado
int main(){
    int size, size2;
    vector<int> V1 = read_vector(size);
    vector<int> V2 = read_vector(size2);
    vector<int> V3 = concatenation(V1,V2);
    for (int i = 0; i < size + size2; ++i) {
        cout <<V3[i];
    }
}
