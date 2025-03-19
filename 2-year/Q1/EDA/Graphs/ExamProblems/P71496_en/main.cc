#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int maximum_save(const vector<vector<pair<int,int>>>& graph) {
    int n = graph.size();
    vector<bool> vis(n, false);
    vis[0] = true;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    for (pair<int,int> x : graph[0]) Q.push(x);
    int sz = 1;
    int sum = 0;
    while (sz < n) {
        int c = Q.top().first;
        int x = Q.top().second;
        Q.pop();
        if (not vis[x]) {
            vis[x] = true;
            for (pair<int,int> y : graph[x]) Q.push(y);
            sum += c;
            ++sz;
        }
    }
    return sum;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<pair<int,int>>> graph(n);
        int v, u, c;
        int cost_total = 0;
        for (int i = 0; i < m; ++i) {
            cin >> v >> u >> c;
            graph[v].push_back({c,u});
            graph[u].push_back({c,v});
            cost_total += c;
        }
        int sol = maximum_save(graph);
        cout << cost_total - sol << endl;
    }
}
