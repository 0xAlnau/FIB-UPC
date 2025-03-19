#include<iostream>
#include<vector>
#include<map>
using namespace std;

const vector<pair<int,int>> dirs_k = {{2,-1}, {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}};
const vector<pair<int,int>> dirs_b = {{-1,-1}, {-1,1}, {1,1}, {1,-1}};
map<pair<int,int>, int> pos2index;

bool pos_ok(int i, int j, vector<vector<char>>& tauler) {
    int n = tauler.size();
    int m = tauler[0].size();
    return i >= 0 and i < n and j >= 0 and j < m;
}

int adventure(vector<vector<char>>& tauler, vector<vector<bool>>& visited, vector<bool>& used, int i, int j, char fitxa) {
    if (visited[i][j]) return 0;
    else {
        int resultat = 0;
        if (tauler[i][j] >= '0' and tauler[i][j] <= '9') {
            resultat += tauler[i][j] - '0';
            tauler[i][j] = '.';
        }
        visited[i][j] = true;
        if (fitxa == 'B') {
            for (pair<int,int> p : dirs_b) {
                int x = i + p.first;
                int y = j + p.second;
                if (pos_ok(x, y, tauler) and tauler[x][y] == 'B') used[pos2index[{x,y}]] = true;
                if (pos_ok(x, y, tauler) and tauler[x][y] != 'T') resultat += adventure(tauler, visited, used, x, y, fitxa);
            }
        }

        else {
            for (pair<int,int> p : dirs_k) {
                int x = i + p.first;
                int y = j + p.second;
                if (pos_ok(x, y, tauler) and tauler[x][y] == 'K') used[pos2index[{x,y}]] = true;
                if (pos_ok(x, y, tauler) and tauler[x][y] != 'T') resultat += adventure(tauler, visited, used, x, y, fitxa);
            }
        }
        return resultat;
    }
}

void count_coins(vector<vector<char>>& tauler, vector<pair<int,int>>& fitxes, int n_coins) {
    int coins = 0;
    int n = tauler.size();
    int m = tauler[0].size();
    int z = fitxes.size();
    vector<bool> used(z, false);
    for (int i = 0; i < z; ++i) {
        if (not used[i]) {
            used[i] = true;
            vector<vector<bool>> visited(n, vector<bool>(m, false));
            if (coins != n_coins) coins += adventure(tauler, visited, used, fitxes[i].first, fitxes[i].second, tauler[fitxes[i].first][fitxes[i].second]);
        }
    }

    cout << coins << endl;
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        vector<vector<char>> tauler(n, vector<char>(m));
        vector<pair<int,int>> fitxes; //indica en quina posició hi ha una fitxa
        int n_coins = 0;
        pos2index.clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> tauler[i][j];
                if (tauler[i][j] == 'K' or tauler[i][j] == 'B') {
                    fitxes.push_back({i, j});
                    pos2index[{i,j}] = fitxes.size() -1;
                }
                else if (tauler[i][j] >= '0' or tauler[i][j] <= '9') n_coins += tauler[i][j] - '0';
            }
        }
        count_coins(tauler, fitxes, n_coins);
    }
}
