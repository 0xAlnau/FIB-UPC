#include<iostream>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,int> P;

int minimum_cost(const vector<vector<P>>& Graph) {
    int n = Graph.size();
    vector<bool> vis(n, false);
    vis[0] = true;
    priority_queue<P, vector<P>, greater<P>> Q;
    for (P x : Graph[0]) Q.push(x);
    int size = 1;
    int sum = 0;

    while (size < n) {
        int c = Q.top().first;
        int v = Q.top().second;
        Q.pop();
        if (not vis[v]) {
            vis[v] = true;
            for (P y : Graph[v]) Q.push(y);
            sum += c;
            ++size;
        }
    }
    return sum;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int v, u, c;
        vector<vector<P>> Graph(n);
        for (int i = 0; i < m; ++i) {
            cin >> v >> u >> c;
            Graph[v-1].push_back({c, u-1});
            Graph[u-1].push_back({c, v-1});
        }
        cout << minimum_cost(Graph) << endl;
    }
}
