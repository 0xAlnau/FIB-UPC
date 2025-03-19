#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
typedef vector<vector<char>> MC;

const vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};
const int INF = numeric_limits<int>::max();

bool pos_ok(const MC& map, int i, int j) {
    int n = map.size();
    int m = map[0].size();
    return i >= 0 and i < n and j >= 0 and j < m and map[i][j] != 'X';
}

int find_second(MC& map, int f, int c) {
    int n = map.size();
    int m = map[0].size();
    vector<vector<int>> dist(n, vector<int>(m, INF));
    dist[f][c] = 0;
    queue<pair<int,int>> Q;
    Q.push({f,c});
    priority_queue<int> treasure_dist;

    while (not Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();
        for (pair<int,int> p : dirs) {
            int i = x + p.first;
            int j = y + p.second;
            if (pos_ok(map, i, j) and dist[i][j] == INF) {
                dist[i][j] = dist[x][y] + 1;
                Q.push({i,j});
                if (map[i][j] == 't') treasure_dist.push(dist[i][j]);
            }
        }
    }
    if (treasure_dist.size() < 2) return -1; //no hi ha tressors pel problema
    else {
        treasure_dist.pop();
        return treasure_dist.top();
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    MC mapa(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> mapa[i][j];
        }
    }
    int f, c;
    cin >> f >> c;

    int distance = find_second(mapa, f-1, c-1);
    if (distance == -1) cout << "we cannot reach two or more treasures" << endl;
    else cout << "second maximum distance: " << distance << endl;
}
