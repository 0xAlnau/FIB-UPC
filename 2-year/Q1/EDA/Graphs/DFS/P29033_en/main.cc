#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<int>> Llista;

bool bipartit(const Llista& llista, vector<int>& colors, int v, int color) {
    bool resultat = true;
    int n = llista[v].size();
    colors[v] = color;

    for (int i = 0; resultat and  i < n; ++i) {
        int u = llista[v][i];
        if (colors[u] == -1) {
            resultat = bipartit(llista, colors, u, 1 - color);
        }
        else if (colors[u] == color) resultat = false;
    }
    return resultat;
}

bool bipartit(const Llista& llista) {    //colors seran 0 i 1
    bool resultat = true;
    int n = llista.size();
    vector<int> colors(n, -1);
    for (int i = 0; resultat and i < n; ++i) {
        if (colors[i] == -1) {
            resultat = bipartit(llista, colors, i, 0); //v = 0 amb color 0
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

        if (bipartit(llista)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
