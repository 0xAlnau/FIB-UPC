#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<limits>
using namespace std;

typedef vector<vector<char>> MC;

const vector<pair<int,int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int INF = numeric_limits<int>::max();

bool pos_correcta(int i, int j, const MC& tauler) {
    int n = tauler.size();
    int m = tauler[0].size();
    return i >= 1 and i < n-1 and j >= 1 and j < m-1 and tauler[i][j] != 'X';
}

void BFS(const MC& tauler, const pair<int,int>& pos_king) {
    int n = tauler.size();
    int m = tauler[0].size();
    vector<vector<pair<int,int>>> prev(n, vector<pair<int,int>>(m));
    vector<vector<int>> dist(n, vector<int>(m,INF));
    dist[pos_king.first][pos_king.second] = 0;

    queue<pair<int,int>> Q;
    Q.push({pos_king.first, pos_king.second});

    bool found = false;
    while (not Q.empty() and not found) {
        int f = Q.front().first;
        int c = Q.front().second;
        Q.pop();
        for (pair<int,int> x : dirs) {
            int i = f + x.first;
            int j = c + x.second;
            if (pos_correcta(i, j, tauler) and dist[i][j] == INF) {
                dist[i][j] = dist[f][c] +1;
                prev[i][j] = {f,c};
                Q.push({i,j});
                if (tauler[i][j] == 'F') {
                    found = true;
                    vector<pair<int,int>> path;
                    pair<int,int> aux = {i,j};
                    while (aux != pos_king) {
                        path.push_back(aux);
                        aux = prev[aux.first][aux.second];
                    }

                    path.push_back(pos_king);
                    cout << dist[i][j] +1 << "  ";
                    int y = path.size();
                    for (int u = y-1; u >= 0; --u) {
                        if (u == 0) cout << path[u].first << " " << path[u].second << endl;
                        else cout << path[u].first << " " << path[u].second << "  ";
                    }
                }
            }

        }
    }
    if (not found) cout << "0" << endl;

}

int main() {
    int n, m;
    while (cin >> n >> m) {
        MC tauler(n, vector<char>(m));
        pair<int,int> pos_king;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> tauler[i][j];
                if (tauler[i][j] == 'K') pos_king = {i,j};
            }
        }
        BFS(tauler, pos_king);
    }
}
