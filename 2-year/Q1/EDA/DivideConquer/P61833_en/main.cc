#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix matrix_pwr(const Matrix& M, int exp, int mod) {
    Matrix resultat(2, vector<int>(2));
    Matrix Aux1(2, vector<int>(2));
    Matrix Aux2(2, vector<int>(2));

    if (exp < 1) {
        resultat[0][0] = 1;
        resultat[0][1] = 0;
        resultat[1][0] = 0;
        resultat[1][1] = 1;
    }

    else if (exp % 2 == 0) {
        Aux1 = matrix_pwr(M, exp/2, mod);
        resultat[0][0] = ((Aux1[0][0] * Aux1[0][0]) + (Aux1[0][1] * Aux1[1][0])) % mod;
        resultat[0][1] = ((Aux1[0][0] * Aux1[0][1]) + (Aux1[0][1] * Aux1[1][1])) % mod;
        resultat[1][0] = ((Aux1[1][0] * Aux1[0][0]) + (Aux1[1][1] * Aux1[1][0])) % mod;
        resultat[1][1] = ((Aux1[1][0] * Aux1[0][1]) + (Aux1[1][1] * Aux1[1][1])) % mod;
    }

    else {
        Aux1 = matrix_pwr(M, exp/2, mod);
        Aux2[0][0] = ((Aux1[0][0] * Aux1[0][0]) + (Aux1[0][1] * Aux1[1][0])) % mod;
        Aux2[0][1] = ((Aux1[0][0] * Aux1[0][1]) + (Aux1[0][1] * Aux1[1][1])) % mod;
        Aux2[1][0] = ((Aux1[1][0] * Aux1[0][0]) + (Aux1[1][1] * Aux1[1][0])) % mod;
        Aux2[1][1] = ((Aux1[1][0] * Aux1[0][1]) + (Aux1[1][1] * Aux1[1][1])) % mod;

        resultat[0][0] = ((Aux2[0][0] * M[0][0]) + (Aux2[0][1] * M[1][0])) % mod;
        resultat[0][1] = ((Aux2[0][0] * M[0][1]) + (Aux2[0][1] * M[1][1])) % mod;
        resultat[1][0] = ((Aux2[1][0] * M[0][0]) + (Aux2[1][1] * M[1][0])) % mod;
        resultat[1][1] = ((Aux2[1][0] * M[0][1]) + (Aux2[1][1] * M[1][1])) % mod;
    }

    return resultat;
}

void cout_matrix(const Matrix& M, int mod) {
    cout << M[0][0] % mod << " " << M[0][1] % mod << endl;
    cout << M[1][0] % mod << " " << M[1][1] % mod << endl;
}

int main() {
    Matrix M(2,vector<int>(2));
    int exp, mod;

    while (cin >> M[0][0] >> M[0][1] >> M[1][0] >> M[1][1] >> exp >> mod) {
        cout_matrix(matrix_pwr(M, exp, mod), mod);
        cout << "----------" << endl;
    }
}
