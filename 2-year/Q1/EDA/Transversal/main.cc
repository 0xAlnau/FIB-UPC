#include<iostream>
#include<vector>
#include<limits>
using namespace std;

const int INF = numeric_limits<int>::max();

void cout_matrix(const vector<vector<int>>& M) {
    int n = M.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (M[i][j] < INF) cout << M[i][j] << " ";
            else cout << "INF ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> floyd_warshall(const vector<vector<int>>& M) {
    int n = M.size(); //obtenim nombre de vèrtexs
    vector<vector<int>> distancia = M;

    for (int i = 0; i < n; ++i) {
        for ( int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (distancia[i][j] > distancia[i][k] + distancia[k][j] and
                    distancia[i][k] != INF and distancia[k][j] != INF) {
                        distancia[i][j] = distancia[i][k] + distancia[k][j];
                    }
            }
        }
    }
    return distancia;
}

int main() {
    int n = 4;
    vector<vector<int>> matrix(n, vector<int>(n, INF));
    matrix[0][0] = 0;
    matrix[0][1] = 5;
    matrix[0][3] = 10;
    matrix[1][1] = 0;
    matrix[2][2] = 0;
    matrix[3][3] = 0;
    matrix[1][2] = 3;
    matrix[2][3] = 1;

    cout_matrix(matrix);

    vector<vector<int>> dist = floyd_warshall(matrix);

    cout_matrix(dist);
}
