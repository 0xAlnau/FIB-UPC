#include<iostream>
#include<vector>
using namespace std;
vector<int> read_in(int size){
    vector<int> V(size);
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}
//esta funcion crea un vector de booleanos, y cuando un
//booleano es true significa que hay empieza una rampas
//Pre: un vector de enteros y su tamaño
//Post: un vector de booleanos con las rampas
vector<bool> ramps_pos(const vector <int>& V, int size){
    vector<bool> num_rampas(size, false);
    for (int i = 0; i < size -2; ++i){
        if (V[i] > V[i + 1] and V[i] > V[i + 2] and V[i + 1] > V[i + 2]) {
            num_rampas[i] = true;
        }
        else if (V[i] < V[i + 1] and V[i] < V[i + 2] and V[i + 1] < V[i +2]) {
            num_rampas[i] = true;
        }
        else{}
    }
    return num_rampas;
}
//esta funcion determinara cuando hay un posible conflicto
//en una rampa
//Pre: un vector de booleanos y su tamaño
//Post: el numero de conflictos
int pot_conflictive(const vector <bool>& B, int size){
    int contador = 0;
    for (int i = 0; i < size - 2; ++i) {
        if (B[i] and B[i + 1] and B[i + 2]) contador = contador + 2;
        else if (B[i] and B[i +1]) ++contador;
        else if (B[i] and B[i + 2]) ++contador;
    }
    return contador;
}
//este programa con la ayuda de dos funciones imprimira
//las posiciones de las rampas de un vector de enteros
//y sus posibles conflictos
//Input: un entero con el tamaño del vector
//Output: una linia con las posiciones de las rampas y
//otra linia con el numero de conflictos
int main(){
    int size = 0;
    while (cin >> size){
        vector<int> v = read_in(size);
        vector<bool> rampas = ramps_pos(v, size);
        cout << "positions with a ramp:";
        for (int i = 0; i < size; ++i) {
            if (rampas[i]) {
                cout <<" "<< i;
            }
        }
        cout <<endl;
        cout << "potentially conflictive: " << pot_conflictive(rampas, size) <<endl;
        cout << "---"<<endl;

    }
}
