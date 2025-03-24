#include<iostream>
#include<vector>
using namespace std;
typedef vector<vector<int>> Matrix;
//esta funcion lee matrizes de tama単o
//m
//Post: un vector con su tamano
Matrix matrix_in(){
    int m;
    cin >> m;
    Matrix M(m,vector<int>(m));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> M [i][j];
        }
    }
    return M;
}

//esta funcion se encarga de coger una matriz
//y trasponerla
//Pre: la matriz a trasponer y su tama単o
//Post: la matriz traspuesta
void transpose(Matrix& m) {
    int s = m.size();
    Matrix A(s,vector<int>(s));
    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            A[j][i] = m[i][j];
        }
    }
    m = A;
}
//este programa con la ayuda de otras funiones,
//se encargara de trasponer una matriz
int main(){
    Matrix my_matrix = matrix_in();
    transpose(my_matrix);
    int s = my_matrix.size();
    for (int k = 0; k < s; ++k) {
        for (int l = 0; l < s; ++l) {
            cout << my_matrix[k][l] << " ";
        }
        cout<<endl;
    }
    cout<<endl;
}



