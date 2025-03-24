#include<iostream>
#include<vector>
#include<string>
using namespace std;
const int LENGTH_ALPHABET = 'z' -'a' - 1;
//esta accion lee un vector y al mismo tiempo calcula
//su tamaño y lo imprime
//Pre: un vector, su tamaño, y la suma
//Post: la suma total
void  read_vector(vector<string> &V, int size, double &suma_longitud){
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
        suma_longitud = suma_longitud + V[i].length();
    }
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << suma_longitud / double(size)<<endl;
}

//Esta funcion dice cual es la letra que mas sale dentro
//de una palabra
//Pre: un string  y su tamaño
//Post: la letra que mas sale
char most_frequent_letter(const string& s, int size) {
    vector<int> Alphabet (LENGTH_ALPHABET, 0);
    for (int i = 0; i < size; ++i) {
        Alphabet[s[i] - 'a'] = Alphabet[s[i] - 'a'] + 1;
    }
    char letra = 'A';
    for (int j = 0; j < LENGTH_ALPHABET; ++j) {
        if (Alphabet[j] != 0) {
            if (letra < 'a') {letra = 'a' + j;}
            else {
                if (Alphabet[j] > Alphabet[letra - 'a']) {letra = 'a' + j;}
            }
        }
    }
    return letra;
}

int main(){
    double suma_longitud = 0;
    int size;
    cin >> size;
    vector<string> V (size);
    read_vector(V,size, suma_longitud);
    for (int i = 0; i < size; ++i) {
        double l = V[i].length();
        if (l >= suma_longitud / size) {
            cout << V[i]<< ": " << most_frequent_letter(V[i],l) <<endl;
        }
        else{}
    }
}

