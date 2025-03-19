#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> Matrix;
/*Uso la matriz especial (1 1) elevada a n-1 para obtener en la posición [0][0] el Fn
 *                       (1 0)
 */
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

int n_fibo(int n, int mod) {
    int resultat = 0;
    if (n == 0) {}
    else {
        Matrix n_fibo_matrix(2,vector<int>(2));
        Matrix matriu_especial(2,vector<int>(2));
        matriu_especial[0][0] = 1;
        matriu_especial[0][1] = 1;
        matriu_especial[1][0] = 1;
        matriu_especial[1][1] = 0;
        n_fibo_matrix = matrix_pwr(matriu_especial, n-1, mod);
        resultat = n_fibo_matrix[0][0]; //Fn en la posició 0 0
    }
    return resultat;
}

int main() {
    int n, mod;
    while (cin >> n >> mod) {
        cout << n_fibo(n, mod) << endl;
    }
}
