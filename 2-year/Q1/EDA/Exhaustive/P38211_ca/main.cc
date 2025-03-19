#include<iostream>
#include<vector>
using namespace std;

bool trobat = false;
void print_queens(int n, vector<vector<char>>& sol, vector<bool>& col, vector<bool>& dig1, vector<bool>& dig2, int i, int queens) {
    if (queens == n) {
        for (int ii = 0; ii < n; ++ii) {
            for (int jj = 0; jj < n; ++jj) {
                cout << sol[ii][jj];
            }
            cout << endl;
        }
        trobat = true;
    }
    else if (i == n) return;
    else if (trobat) return;
    else {
        for (int j = 0; j < n; ++j) {
            if (not col[j] and not dig1[i+j] and not dig2[i-j+n-1]) {
                col[j] = true;
                dig1[i+j] = true;
                dig2[i-j+n-1] = true;
                sol[i][j] = 'Q';

                print_queens(n, sol, col, dig1, dig2, i+1, queens+1);

                sol[i][j] = '.';
                col[j] = false;
                dig1[i+j] = false;
                dig2[i-j+n-1] = false;
            }
        }
    }
}

void print_queens(int n) {
    vector<vector<char>> sol(n, vector<char>(n, '.'));
    vector<bool> col(n, false); // si hi ha reina a la columna j;
    vector<bool> dig1(2*n-1, false); // si hi ha reina a la diagonal i + j
    vector<bool> dig2(2*n-1, false); //si hi ha reina a la diagonal i - j + n -1
    int i = 0;
    int queens = 0;
    trobat = false;
    print_queens(n, sol, col, dig1, dig2, i, queens);
    if (not trobat) cout << "NO SOLUTION" << endl;
}

int main() {
    int n;
    cin >> n;
    print_queens(n);
}
