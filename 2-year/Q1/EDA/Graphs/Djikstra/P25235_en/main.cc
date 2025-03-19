#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;
typedef vector<vector<pair<int,int>>> Llista;

const int INF = numeric_limits<int>::max();

pair<int,int> djikstra(const Llista& llista, int x, int y) {
    int n = llista.size();
    vector<int> steps(n, 0);
    vector<int> dist(n, INF);
    vector<bool> visited(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;

    dist[x] = 0;
    Q.push({0, x});

    while (not Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        if (not visited[u]) {
            visited[u] = true;
            for (pair<int,int> p : llista[u]) {
                int v = p.second;
                int c = p.first;
                if (dist[u] + c < dist[v]) {
                    dist[v] = dist[u] + c;
                    Q.push({dist[v], v});
                    steps[v] = steps[u] + 1;
                }
                //DIFERENCIA, NO UNIQUE PATH, CAL COMRPOBAR QUIN ES MILLOR
                else if (dist[v] == dist[u] + c and steps[v] > steps[u] + 1) {
                    steps[v] = steps[u] + 1;
                }
            }
        }
    }

    return {dist[y], steps[y]};
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Llista llista(n);
        int v, u; // v->u amb cost c
        double c;
        for (int i = 0; i < m; ++i) {
            cin >> v >> u >> c;
            llista[v].push_back({c,u});
        }
        int x, y;
        cin >> x >> y;
        pair<double,int> resultat = djikstra(llista, x, y);

        if (resultat.first == INF) cout << "no path from " << x << " to " << y << endl;
        else cout << "cost " << resultat.first << ", " << resultat.second << " step(s)" << endl;
    }
}
