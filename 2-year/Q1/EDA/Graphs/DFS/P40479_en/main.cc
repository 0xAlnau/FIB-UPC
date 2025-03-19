#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<string>> MatrixS;
typedef vector<vector<bool>> MatrixB;
//                             esq      dret    amunt    abaix
vector<pair<int,int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

bool existeix_vei(const MatrixS& M, int i, int j) {
    int n = M.size();
    int m = M[0].size();
    return i >= 0 and i < n and j >= 0 and j < m;
}

void paint_board(MatrixS& resultat, MatrixB& visited, int i, int j, string dibuix) {
    visited[i][j] = true;

    for (pair<int,int> p : dirs) {
        int ii = i + p.first;
        int jj = j + p.second;

        if (existeix_vei(resultat, ii, jj) and not visited[ii][jj] and resultat[ii][jj] != "#") {
            resultat[ii][jj] = dibuix;
            paint_board(resultat, visited, ii, jj, dibuix);
        }
    }

}

MatrixS paint_board(const MatrixS& M) {
    MatrixS resultat = M;
    int n = M.size();
    int m = M[0].size();
    MatrixB visited(n, vector<bool>(m, false));

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (not visited[i][j] and resultat[i][j] != "." and resultat[i][j] != "#") {
                paint_board(resultat, visited, i, j, resultat[i][j]);
            }
        }
    }


    return resultat;
}

void printMatrix(const MatrixS& M) {
    int n = M.size();
    int m = M[0].size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << M[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        string linia;
        MatrixS M(n, vector<string>(m));
        for (int i = 0; i < n; ++i) {
            cin >> linia;
            for (int j = 0; j < m; ++j) {
                M[i][j] = linia[j];
            }
        }
        MatrixS resultat = paint_board(M);
        printMatrix(resultat);
    }
}
