#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
const int INF = numeric_limits<int>::max();
const vector<pair<int,int>> dirs_c = {{-2,-1},{-2,1},{-1,2},{-1,-2},{1,2},{1,-2},{2,-1},{2,1}};
typedef vector<vector<char>> MC;

bool pos_ok(const MC& M, int i, int j) {
    int n = M.size();
    int m = M[0].size();
    return i >= 0 and i < n and j >= 0 and j < m and M[i][j] != 'a';
}

void menja_flors(const MC& M, int f, int c) {
    int n = M.size();
    int m = M[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INF));
    dist[f][c] = 0;
    queue<pair<int,int>> Q;
    Q.push({f,c});
    int flors = 0;
    double distancia_flors = 0;

    while (not Q.empty()) {
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();
        for (pair<int,int> p : dirs_c) {
            int x = i + p.first;
            int y = j + p.second;
            if (pos_ok(M, x, y) and dist[x][y] == INF) {
                dist[x][y] = dist[i][j] + 1;
                Q.push({x,y});
                if (M[x][y] == 'F') {
                    ++flors;
                    distancia_flors += dist[x][y];
                }
            }
        }
    }
    if (flors == 0) cout << "el cavall no pot arribar a cap flor" << endl;
    else {
        cout << "flors accessibles: " << flors << endl;
        cout << "distancia mitjana: " << distancia_flors / flors << endl;
    }
}

int main() {
    cout.setf(ios::fixed);
    cout.precision(4);
    int n, m;
    cin >> n >> m;
    MC tauler(n, vector<char>(m));
    pair<int,int> C;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> tauler[i][j];
            if (tauler[i][j] == 'C') C = {i,j};
        }
    }
    menja_flors(tauler, C.first, C.second);
}
