#include<iostream>
#include<vector>
#include<queue>
#include<limits>
using namespace std;

typedef vector<vector<pair<int,int>>> Llista;

const int INF = numeric_limits<int>::max();

pair<int,int> dijkstra(const Llista& llista, int x, int y) {
    int n = llista.size();

    vector<bool> visited(n, false);
    vector<int> ways(n, 0);
    vector<int> dist(n, INF);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;

    ways[x] = 1;
    dist[x] = 0;
    Q.push({0,x});

    while (not Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        if (not visited[u]) {
            visited[u] = true;
            for (pair<int,int> p : llista[u]) {
                int v = p.second;
                int c = p.first;
                if (dist[v] > dist[u] + c) {
                    dist[v] = dist[u] + c;
                    Q.push({dist[v], v});
                    ways[v] = ways[u];
                }

                else if (dist[v] == dist[u] + c) ways[v] += ways[u];
            }
        }
    }
    return {dist[y], ways[y]};
}


int main() {
    int n, m;
    while (cin >> n >> m) {
        Llista llista(n);
        int v, u, c; //v->u with cost c
        for (int i = 0; i < m; ++i) {
            cin >> v >> u >> c;
            llista[v].push_back({c,u});
        }
        int x, y;
        cin >> x >> y;
        pair<int,int> resultat = dijkstra(llista, x, y);
        if (resultat.first == INF) cout << "no path from " << x << " to " << y << endl;
        else cout << "cost " << resultat.first << ", " << resultat.second << " way(s)" << endl;
    }
}
