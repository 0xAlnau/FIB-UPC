#include<iostream>
#include<vector>
using namespace std;

const vector<pair<int,int>> dirs = {{0,1}, {0,-1}, {1,0}, {-1,0}};

bool pos_ok(const vector<vector<char>>& camp, int i, int j) {
    int n = camp.size();
    int m = camp[0].size();
    return i >= 0 and i < n and j >= 0 and j < m;
}

void write_ways(const vector<vector<char>>& camp, vector<char>& sol, vector<vector<bool>>& used, int a, int b, int c, int d) {
    if (a == c and b == d) {
        sol.push_back(camp[c][d]);
        int n = sol.size();
        for (int i = 0; i < n; ++i) cout << sol[i];
        cout << endl;
        sol.pop_back();
    }
    else {
        for (pair<int,int> p : dirs) {
            int x = a + p.first;
            int y = b + p.second;
            if (pos_ok(camp, x, y) and not used[x][y]) {
                sol.push_back(camp[a][b]);
                used[a][b] = true;

                write_ways(camp, sol, used, x, y, c, d);

                used[a][b] = false;
                sol.pop_back();
            }
        }
    }
}

void write_ways(const vector<vector<char>>& camp, int a, int b, int c, int d) {
    int n = camp.size();
    int m = camp[0].size();
    vector<vector<bool>> used(n, vector<bool>(m, false));
    vector<char> sol;
    write_ways(camp, sol, used, a, b, c, d);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> camp(n, vector<char>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> camp[i][j];
        }
    }
    int f_ini, c_ini, f_fin, c_fin;
    cin >> f_ini >> c_ini >> f_fin >> c_fin;

    write_ways(camp, f_ini, c_ini, f_fin, c_fin);
}
