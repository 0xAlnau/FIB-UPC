#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void write_ways(const vector<vector<int>>& dag, vector<int>& ge) {
    int n = dag.size();
    priority_queue<int, vector<int>, greater<int>> grau_zero;
    vector<int> ordre;
    for (int i = n-1; i >= 0; --i) if (ge[i] == 0) grau_zero.push(i);

    while (not grau_zero.empty()) {
        int v = grau_zero.top();
        ordre.push_back(v);
        grau_zero.pop();

        for (int x : dag[v]) {
            --ge[x];
            if (ge[x] == 0) grau_zero.push(x);
        }
    }
    int size = ordre.size();
    for (int j = 0; j < size; ++j) {
        if (j == size -1) cout << ordre[j] << endl;
        else cout << ordre[j] << " ";
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> dag(n);
        vector<int> ge(n, 0);
        int v, u;
        for (int i = 0; i < m; ++i) {
            cin >> v >> u;
            dag[v].push_back(u);
            ++ge[u];
        }
        write_ways(dag, ge);
    }
}
