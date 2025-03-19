#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<char>> MC;

const vector<pair<int,int>> dirs_g = {{0,-1}, {0,1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
const vector<pair<int,int>> dirs_p = {{0,-1}, {0,1}, {1,0}, {-1,0}};

bool pos_ok(const MC& tauler, int i, int j) {
    int n = tauler.size();
    int m = tauler[0].size();
    return i >= 0 and i < n and m >= 0 and j < m and tauler[i][j] != 'X';
}

bool near_ghost(const MC& tauler, int f, int c) {
    for (pair<int,int> x : dirs_g) {
        int i = f + x.first;
        int j = c + x.second;
        if (pos_ok(tauler, i, j) and tauler[i][j] == 'F') return true;
    }
    return false;
}

bool DFS(const MC& tauler, int f, int c, vector<vector<bool>>& vis) {
    bool resultat = false;
    if (vis[f][c]) resultat = false;
    else {
        vis[f][c] = true;
        if (near_ghost(tauler, f, c)) resultat = false;
        else {
            if (tauler[f][c] == 'B') resultat = true;
            else {
                for (int x = 0; not resultat and x < 4; ++x) {
                    int i = f + dirs_p[x].first;
                    int j = c + dirs_p[x].second;
                    if (pos_ok(tauler, i, j)) resultat = DFS(tauler, i, j, vis);
                }
            }
        }
    }
    return resultat;
}

bool DFS(const MC& tauler, pair<int,int> pac) {
    int n = tauler.size();
    int m = tauler[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    return DFS(tauler, pac.first, pac.second, vis);

}

int main() {
    int n, m;
    while (cin >> n >> m) {
        MC tauler(n, vector<char>(m));
        pair<int,int> pac;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> tauler[i][j];
                if (tauler[i][j] == 'P') pac = {i,j};
            }
        }
        if (DFS(tauler, pac)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
