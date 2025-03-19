#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> Llista;

bool cyclic(const Llista& llista, int v, vector<bool>& visited, vector<int>& fathers) {
    bool resultat = false;
    if (visited[v]) resultat = true;
    else {
        visited[v] = true;
        for (int u : llista[v]) {
            if (fathers[v] != u) {
                fathers[u] = v;
                if (cyclic(llista, u, visited, fathers)) resultat = true;
            }
        }
    }
    return resultat;
}

int count_trees(const Llista& llista) {
    int resultat = 0;
    int n = llista.size();
    vector<bool> visited(n, false);
    vector<int> fathers(n, -1);

    for (int i = 0; resultat != -1 and i < n; ++i) {
        if (not visited[i]) {
            if (cyclic(llista, i, visited, fathers)) resultat = -1;
            else ++resultat;
        }
    }
    return resultat;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        Llista llista(n);
        int x, y;
        for (int i = 0; i < m; ++i) {
            cin >> x >> y;
            llista[x].push_back(y);
            llista[y].push_back(x);
        }

        int d = count_trees(llista);
        if (d == -1) cout << "no" << endl;
        else cout << d << endl;
    }
}
