#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<limits>
using namespace std;
//                             dret     esq     amunt    avall
vector<pair<int,int>> dirs = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
const int INF = numeric_limits<int>::max();
typedef vector<vector<char>> Matrix;

bool vei_existeix(Matrix& M, int f, int c) {
    int n = M.size();
    int m = M[0].size();

    return (f >= 0 and f < n and c >= 0 and c < m and M[f][c] != 'X');
}

int funcio_bfs(Matrix& M, int f, int c) {
    int resultat;
    int n = M.size();
    int m = M[0].size();
    vector<vector<int>> distancies(n, vector<int>(m, INF));
    distancies[f][c] = 0;

    queue<pair<int,int>> Q;
    Q.push({f, c});

    set<int> dist2t;

    while (not Q.empty()) {
        pair<int,int> coord = Q.front();
        Q.pop();

        for (int i = 0; i < 4; ++i) {
            int f_vei = coord.first + dirs[i].first;
            int c_vei = coord.second + dirs[i].second;

            if (vei_existeix(M, f_vei, c_vei) and distancies[f_vei][c_vei] == INF) {
                Q.push({f_vei, c_vei});
                distancies[f_vei][c_vei] = distancies[coord.first][coord.second] + 1;
                if (M[f_vei][c_vei] == 't') dist2t.insert(distancies[f_vei][c_vei]);
            }
        }
    }

    if (dist2t.empty()) resultat = -1;
    else {
        auto it = dist2t.end();
        --it;
        resultat = *it;
    }
    return resultat;
}

int main() {
    int files, columnes;
    cin >> files >> columnes;

    Matrix M(files, vector<char>(columnes));
    for (int i = 0; i < files; ++i) {
        for(int j = 0; j < columnes; ++j) {
            cin >> M[i][j];
        }
    }

    int f, c;
    cin >> f >> c;

    int d = funcio_bfs(M, f-1, c-1);
    if (d == -1) cout << "no treasure can be reached" << endl;
    else cout << "maximum distance: " << d << endl;
}
