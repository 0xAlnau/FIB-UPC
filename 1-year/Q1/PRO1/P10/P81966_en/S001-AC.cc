#include <iostream>
#include <vector>
using namespace std;

vector<double> read_vector(){
    int size;
    cin >> size;
    vector<double> V(size);
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}

int position(double x, const vector<double>& v, int left, int right){
    if (left > right) {
        return -1;
    }
    else {
        int element = (left + right) / 2;
        if (x < v[element]){
            return position(x, v, left, element - 1);
        }
        else if (x > v[element]) {
            return position(x, v, element + 1, right);
        }
        else return element;
    }
}

int main() {
    vector<double> numeros = read_vector();
    double elemento;
    cin >> elemento;
    int size = numeros.size();
    int left = 0, right = size -1;
    cout << position(elemento, numeros, left, right) <<endl;
}

