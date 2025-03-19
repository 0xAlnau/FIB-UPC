#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;

void write_ways(const vector<vector<int>>& dag, vector<int>& ge, const vector<string>& noms, map<string,int>& s2i) {
    int n = dag.size();
    vector<int> sol;
    priority_queue<string, vector<string>, greater<string>> Q;

    for (int i = 0; i < n; ++i) if (ge[i] == 0) Q.push(noms[i]);

    while (not Q.empty()) {
        string v = Q.top();
        Q.pop();
        sol.push_back(s2i[v]);
        for (int u : dag[s2i[v]]) {
            --ge[u];
            if (ge[u] == 0) Q.push(noms[u]);
        }
    }
    int size = sol.size();
    if (size != n) cout << "NO VALID ORDERING" << endl;
    else {
        for (int j = 0; j < size; ++j) {
            cout << noms[sol[j]];
        }
        cout << endl;
    }
}

int main() {
    int n;
    while (cin >> n) {
        string s;
        vector<vector<int>> dag(n);
        vector<string> noms(n);
        map<string,int> s2i;
        vector<int> ge(n,0);
        for (int i = 0; i < n; ++i) {
            cin >> s;
            noms[i] = s;
            s2i[s] = i;
        }
        int m;
        cin >> m;
        string s2;
        for (int j = 0; j < m; ++j) {
            cin >> s >> s2;
            dag[s2i[s]].push_back(s2i[s2]);
            ++ge[s2i[s2]];
        }
        write_ways(dag, ge, noms, s2i);
    }
}
