#include<iostream>
#include<vector>
using namespace std;

bool cyclic(const vector<vector<int>>& g, vector<bool>& vis, vector<bool>& recorregut, int v) {
    bool resultat = false;
    if (recorregut[v]) resultat = true;
    else {
        if (vis[v]) resultat = false;
        else {
            vis[v] = true;
            recorregut[v] = true;

            for (int u : g[v]) {
                if (cyclic(g, vis, recorregut, u)) return true;
            }
            recorregut[v] = false;
        }
    }

    return resultat;
}

bool cyclic(const vector<vector<int>>& g) {
    bool resultat = false;
    int n = g.size();
    vector<bool> vis(n,false);
    vector<bool> recorregut(n, false);
    for (int i = 0; not resultat and i < n; ++i) {
        if (not vis[i]) resultat = cyclic(g, vis, recorregut, i);
    }
    return resultat;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(n);
        int v, u;
        for (int i = 0; i < m; ++i) {
            cin >> v >> u;
            g[v].push_back(u);
        }
        if (cyclic(g)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
