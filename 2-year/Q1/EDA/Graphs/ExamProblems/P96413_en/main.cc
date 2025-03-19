#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;

const int INF = numeric_limits<int>::max();

void print_erdos(const vector<vector<int>>& v) {
    int n = v.size();
    vector<int> dist(n, INF);
    queue<int> Q;
    Q.push(0); //erdos
    dist[0] = 0; //erdos

    while (not Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int x : v[u]) {
            if (dist[x] == INF) {
                dist[x] = dist[u] + 1;
                Q.push(x);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << i << " : ";
        if (dist[i] == INF) cout << "no" << endl;
        else cout << dist[i] << endl;
    }
    cout << "----------" << endl;
}

int main() {
    int n, w;
    while (cin >> n >> w) {
        vector<vector<int>> authors(n);
        for (int i = 0; i < w; ++i) {
            int n2;
            cin >> n2;
            vector<int> aux(n2);
            int nx;
            for (int j = 0; j < n2; ++j) {
                cin >> nx;
                aux[j] = nx;
            }

            for (int k = 0; k < n2; ++k) {
                for (int l = 0; l < n2; ++l) {
                    if (k != l) {
                        authors[aux[k]].push_back(aux[l]);
                    }
                }
            }
        }
        print_erdos(authors);
    }
}
