#include<iostream>
#include<vector>
using namespace std;
typedef vector<vector<int>> Matrix;

Matrix read_matrix(int filas, int columnas){
    Matrix M(filas,vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin >> M[i][j];
        }
    }
    return M;
}

//esta accion cogera unas posiciones de un rectangulo
//de una matriz y las transormara en 0
//Pre: una matriz de enteros y dos enteros
void turn_zeros(Matrix& M, int row, int column){
    int filas = M.size();
    int columnas = M[0].size();
    int i = row;
    while (i < filas and M[i][column] != 0) {
        int j = column;
        while (j < columnas and M[i][j] != 0) {
            M[i][j] = 0;
            ++j;
        }
        ++i;
    }
}

//esta funcion se encarga de contar cuantos 'campos'
//hay en una matriz de enteros
//Pre: una matriz de enteros, y dos naturales indicando
//su tamaño
//Post: un natural con el numero de campos
int count_fields(Matrix& Mveg){
    int contador = 0;
    int filas = Mveg.size();
    int columnas = Mveg[0].size();
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (Mveg[i][j] != 0) {
                turn_zeros(Mveg, i, j);
                ++contador;
            }

        }
    }
    return contador;
}

//este programa con la ayuda de las dos otras funciones
//se encarga de imprimir cuantos campos hay dentro de
//una matriz de enteros con 'campos'
//input: dos naturales indicando el tamaño de la matriz
//output: una linia con el numero de campos
int main(){
    int filas, columnas;
    while (cin >> filas >> columnas) {
        Matrix fields = read_matrix(filas, columnas);
        cout << count_fields(fields) <<endl;
    }
}

