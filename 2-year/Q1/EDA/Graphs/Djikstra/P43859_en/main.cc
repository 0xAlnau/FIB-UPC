#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
const int INF = numeric_limits<int>::max(); // o posar INT_MAX o 2e9;

int dist(const vector<vector<pair<int,int>>> G, int x, int y) {
    int n = G.size();
    vector<int> dist(n, INF);
    vector<bool> removed(n, false);
    dist[x] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q; //petit a gran
    Q.push({0, x}); // afegim dist, vert

    while (not Q.empty()) {
        int u = Q.top().second; //agafem el més petit
        Q.pop();
        if (u == y) return dist[y];

        if (not removed[u]) {
            removed[u] = true;
            for (pair<int,int> p : G[u]) {
                int v = p.second;
                int c = p.first;
                if (dist[u] + c  < dist[v]) {
                    dist[v] = dist[u] + c;
                    Q.push({dist[v], v});
                }
            }
        }
    }

    if (dist[y] == INF) return -1;
    else return dist[y];
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        //u->v amb cost c
        vector<vector<pair<int,int>>> G(n); //pairs are <cost, vertex>
        int u, v, c;
        for (int i = 0; i < m; ++i) {
            cin >> u >> v >> c;
            G[u].push_back({c, v});
        }
        int x, y;
        cin >> x >> y; //distance x to y
        int d = dist(G, x, y);
        if (d == -1) cout << "no path from " << x << " to " << y << endl;
        else cout << d << endl;
    }
}
