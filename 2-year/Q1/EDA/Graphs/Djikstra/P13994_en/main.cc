#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
const int INF = numeric_limits<int>::max();

vector<int> djikstra(const vector<vector<pair<int,int>>>& G, int x, int y) {
    vector<int> resultat;

    int n_ver = G.size();
    vector<int> dist(n_ver, INF);
    vector<bool> removed(n_ver, false);
    vector<int> previ(n_ver, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q; //petit a gran

    dist[x] = 0;
    Q.push({0, x});

    bool found = false;
    while (not Q.empty() and not found) {
        int u = Q.top().second;
        Q.pop();

        if (u == y) {
            found = true;
            int aux = y;
            while (aux != x) {
                resultat.push_back(aux);
                aux = previ[aux];
            }
            resultat.push_back(x);
        }

        if (not removed[u] and not found) {
            removed[u] = true;
            for (pair<int,int> p : G[u]) {
                int v = p.second;
                int c = p.first;
                if (dist[u] + c < dist[v]) {
                    dist[v] = dist[u] + c;
                    Q.push({dist[v], v});
                    previ[v] = u;
                }
            }
        }
    }
    return resultat;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int,int>>> G(n);
        int v, u, c;
        for (int i = 0; i < m; ++i) {
            cin >> v >> u >> c;
            G[v].push_back({c,u}); //pair vertex i cost
        }
        int x,y;
        cin >> x >> y;
        vector<int> resultat = djikstra(G, x, y);
        if (resultat.size() == 0) cout << "no path from " << x << " to " << y << endl;
        else {
            bool first = true;
            int size = resultat.size();
            for (int j = size-1; j >= 0; --j) {
                if (first) {
                    first = false;
                    cout << resultat[j];
                }
                else cout << " " << resultat[j];
            }
            cout << endl;
        }
    }
}
