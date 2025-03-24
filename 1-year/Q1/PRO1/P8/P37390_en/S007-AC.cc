#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<int>> Matrix;

Matrix read_matrix(int size){
    Matrix M(size, vector<int> (size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cin >> M[i][j];
        }
    }
    return M;
}

void matrix_out(const Matrix& M){
    int size = M.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << M[i][j] << " ";
        }
        cout<< endl;
    }
    cout <<endl;
}
//esta funcion calculara el producto de dos matrices
//Pre: dos matrices de enteros
//Post: una matriz con el resultado
Matrix product(const Matrix& A, const Matrix& B){
    int size = A.size();
    Matrix C (size, vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }
    return C;
}
//este programa con la ayuda de las otras tres
//funciones dara el resultado del producto de
//dos matrices
int main(){
    int n;
    while (cin >> n) {
        Matrix A = read_matrix(n);
        Matrix B = read_matrix(n);
        Matrix C = product(A,B);
        matrix_out(C);
    }
}
