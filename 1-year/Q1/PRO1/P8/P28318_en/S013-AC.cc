#include<iostream>
#include<vector>
using namespace std;
typedef vector<vector<int>> Matrix;
//esta funcion leera una matriz de enteros
//Pre: dos enteros vacios para guardar su tamaÃ±o
//Post: una matriz de enteros
Matrix matrix_in(){
    int size1, size2;
    cin >> size1 >> size2;
    Matrix M(size1 + 1, vector<int>(size2 +1));
    for (int i = 1; i <= size1; ++i) {
        for (int j = 1; j <= size2; ++j) {
            cin >> M[i][j];
        }
    }
    return M;
}

//esta accion se encarga de imprimir la fila
//deseada por el usuario
//Pre: una matriz y el numero de columnas
//Post: la fila deseada
void rows(const Matrix& Menu){
    int size2 = Menu[0].size();
    int row;
    cin >> row;
    cout << "row " << row << ":";
    for (int i = 1; i < size2; ++i) {
        cout << " " << Menu[row][i];
    }
    cout<< endl;
}

//esta accion se encarga de imprimir la columna
//deseada por el usuario
//Pre: una matriz y el numero de filas
//Post: la columna deseada
void columns(const Matrix& Menu){
    int size1 = Menu.size();
    int column;
    cin >> column;
    cout << "column " << column << ":";
    for (int i = 1; i < size1; ++i) {
        cout << " " << Menu[i][column];
    }
    cout<< endl;
}

//esta accion imprimira un elemento en
//concreto de una matriz
//Pre: una matriz de enteros
//Post: el elemento deseado
void elements(const Matrix& Menu){
    int i, j;
    cin >> i >> j;
    cout << "element " << i << " " << j <<": " << Menu[i][j] <<endl;
}

//el programa principal con la ayuda
//de las otras acciones imprimira las
//filas, columnas y elementos deseados
//por el usuario
int main(){
    Matrix Menu = matrix_in();
    string question;
    while (cin >> question) {
        if (question == "row") rows(Menu);
        else if (question == "column") columns(Menu);
        else if (question == "element") elements(Menu);
    }
}
