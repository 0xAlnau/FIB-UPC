#include<iostream>
#include<vector>
#include<string>
using namespace std;

typedef vector<vector<string>> MatrixS;
typedef vector<vector<bool>> MatrixB;
//                           adalt esq  adalt dret abaix esq  abaix dret
vector<pair<int,int>> dirs = {{-1, -1},  {-1, 1},   {1, -1},   {1, 1}};

bool pos_valida(const MatrixS& M, int i, int j) {
    int n = M.size();
    int m = M[0].size();
    return i >= 0 and i < n and j >= 0 and j < m;
}

void same_bishops(const MatrixS& M, MatrixB& visited, int& n_bishops, int& tot_bishops, int i, int j) {
    visited[i][j] = true;
    if (M[i][j] != "X") {
        ++n_bishops;
        tot_bishops += atoi(M[i][j].c_str());
    }

    for (pair<int,int> p : dirs) {
        int ii = i + p.first;
        int jj = j + p.second;
        if (pos_valida(M, ii, jj) and not visited[ii][jj] and M[ii][jj] != "X") same_bishops(M, visited, n_bishops, tot_bishops, ii, jj);
    }
}

bool same_bishops(const MatrixS& M) {
    bool resultat = true;
    int n = M.size();
    int m = M[0].size();
    MatrixB visited(n, vector<bool>(m, false));
    int prev_tot = -1;

    for (int i = 0; resultat and i < n; ++i) {
        for (int j = 0; resultat and j < m; ++j) {
            if (not visited[i][j] and M[i][j] != "X") {
                visited[i][j] = true;
                int n_bishops = 0;
                int tot_bishops = 0;
                same_bishops(M, visited, n_bishops, tot_bishops, i, j);

                if (tot_bishops % n_bishops == 0) {
                    if (prev_tot == -1) prev_tot = tot_bishops / n_bishops;
                    else {
                        if (prev_tot != tot_bishops / n_bishops) resultat = false;
                    }
                }

                else resultat = false;
            }
        }
    }

    return resultat;
}

int main() {
    int casos;
    cin >> casos;
    for (int t = 1; t <= casos; ++t) {
        int n, m;
        cin >> n >> m;
        MatrixS M(n, vector<string>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> M[i][j];
            }
        }

        if (same_bishops(M)) {
            cout << "Case " << t << ": yes" << endl;
        } else {
            cout << "Case " << t << ": no" << endl;
        }
    }
}
