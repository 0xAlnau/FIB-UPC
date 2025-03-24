#include<iostream>
#include<vector>
using namespace std;
const int INITIAL_VALUE = 1000000000;
const int SIZE = 1001;
vector<int> read_vector() {
    int size;
    cin >> size;
    vector<int> v (size);
    for (int i = 0; i < size; ++i) {
        cin >> v[i];
    }
    return v;
}
//este programa leera una seceuncia de naturales
//y dira cuantas veces aparece cada uno
//input: un numero natural n seguido de n numero en el
//intervalo 1000000000 <= n <= 1000001000
//output: una linia por cada numero diciendo cuantas veces
//se repite
int main(){
    vector <int> v = read_vector();
    vector <int> freq (SIZE, 0);
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        ++freq[v[i] % 10000];
    }
    for (int j = 0; j < SIZE; ++j) {
        if (freq[j] != 0) {
            cout << INITIAL_VALUE + j << " : " << freq[j] <<endl;
        }
        else{}
    }

}


