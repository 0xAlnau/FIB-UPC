#include<iostream>
#include<vector>
using namespace std;
//                              dret   esq    avall   amunt
vector<pair<int,int>> dirs = { {0,1}, {0,-1}, {1,0}, {-1,0}};
typedef vector<vector<char>> Matrix;

bool existeix_vei(Matrix& M, int f, int c) {
    int n = M.size();
    int m = M[0].size();

    return f >= 0 and f < n and c >= 0 and c < m and M[f][c] != 'X';
}

int funcio_dfs(Matrix& M, int f, int c) {
    int resultat = 0;
    if (M[f][c] == 't') ++resultat;
    M[f][c] = 'X';

    for (int i = 0; i < 4; ++i) {
        int f_vei = f + dirs[i].first;
        int c_vei = c + dirs[i].second;

        if (existeix_vei(M, f_vei, c_vei)) resultat += funcio_dfs(M, f_vei, c_vei);

    }
    return resultat;
}

int main() {
    int files, columnes;
    cin >> files >> columnes;

    Matrix tauler(files, vector<char>(columnes));
    for (int i = 0; i < files; ++i) {
        for (int j = 0; j < columnes; ++j) {
            cin >> tauler[i][j];
        }
    }

    int f, c;
    cin >> f >> c;
    cout << funcio_dfs(tauler, f-1, c-1) << endl;
}

