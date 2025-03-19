#include<iostream>
#include<vector>
using namespace std;

const vector<pair<int,int>> dirs = {{-1,0}, {1,0}, {0,1}, {0,-1}, {-1,-1}, {-1,1}, {1,1}, {1,-1}};

bool pos_ok(int i, int j, int n) {
    return i >= 0 and i < n and j >= 0 and j < n;
}

void write_kings(int n, int k, vector<vector<char>>& sol, int kings, int i, int j) {
    if (k == kings) {
        for (int ii = 0; ii < n; ++ii) {
            for (int jj = 0; jj < n; ++jj) {
                if (jj == n-1) cout << sol[ii][jj] << endl;
                else cout << sol[ii][jj];
            }
        }
        cout << "----------" << endl;
    }

    else if (i == n) return;

    else {
        if (sol[i][j] == '.') {
            bool trobat = false;
            for (pair<int,int> u : dirs) {
                int x = i + u.first;
                int y = j + u.second;
                if (pos_ok(x, y, n) and sol[x][y] == 'K') trobat = true;
            }
            if (!trobat) {
                sol[i][j] = 'K';

                if (j < n-1) write_kings(n, k, sol, kings+1, i, j+1);
                else write_kings(n, k, sol, kings+1, i+1, 0);

                sol[i][j] = '.';
            }
        }
        if (j < n-1) write_kings(n, k, sol, kings, i, j+1);
        else write_kings(n, k, sol, kings, i+1, 0);
    }
}

void write_kings(int n, int k) {
    vector<vector<char>> sol(n, vector<char>(n, '.'));
    write_kings(n, k, sol, 0, 0, 0);
}

int main() {
    int n, k;
    cin >> n >> k;
    write_kings(n, k);
}
