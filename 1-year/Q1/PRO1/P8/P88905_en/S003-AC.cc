#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;
Matrix read_in(int size, int size2){
    Matrix M(size, vector<int>(size2));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size2; ++j) {
            cin >> M[i][j];
        }
    }
    return M;
}

void matrix_out(const Matrix& M, int size, int size2){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size2; ++j) {
            cout << M[i][j] << " ";
        }
        cout <<endl;
    }
    cout<< endl;
}
//esta funcion calculara el producto de dos matrices
//que pueden tener diferente tamaño
//Pre: dos matrices con tamaño pxq y qxr
//Post: una matriz de enteros de pxr
Matrix product(const Matrix& A, const Matrix& B) {
    int nfiles = A.size();
    int ncolumns = B[0].size();
    int common_size = B.size();

    Matrix C(nfiles, vector<int>(ncolumns, 0));

    for (int i = 0; i < nfiles; ++i) {
        for (int j = 0; j < ncolumns; ++j) {
            for (int k = 0; k < common_size; ++k) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
//este programa con la ayuda de las otras
//funciones calculara el producto de dos
//matrices de enteros pxq y qxr
//Input: p, q y r
int main(){
    int p, q, r;
    while (cin >> p >> q >> r) {
        Matrix A = read_in(p,q);
        Matrix B = read_in(q,r);
        Matrix C = product(A,B);
        matrix_out(C,p,r);
    }
}

