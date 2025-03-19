#include<iostream>
#include<vector>
#include<map>
using namespace std;

typedef vector<vector<bool>> Matrix;

void escriure_compatibles(const vector<char>& species, const vector<string>& compatible, vector<bool>& usat, vector<int>& sol, const Matrix& matriu) {
    int n = species.size();
    if (n == sol.size()) {
        for (int x : sol) cout << species[x];
        cout << endl;
    }

    else {
        for (int i = 0; i < n; ++i) {
            if (not usat[i]) {
                if (sol.size() == 0) {
                    sol.push_back(i);
                    usat[i] = true;
                    escriure_compatibles(species, compatible, usat, sol, matriu);

                    usat[i] = false;
                    sol.pop_back();
                }

                else { //mirar enrere a veures si es pot mirar qui tinc enrere
                    int n_sol = sol.size();
                    int indx = sol[n_sol-1]; //agafem l'animal
                    if (not matriu[indx][i]) {
                        sol.push_back(i);
                        usat[i] = true;
                        escriure_compatibles(species, compatible, usat, sol, matriu);

                        usat[i] = false;
                        sol.pop_back();
                    }
                }
            }
        }
    }
}

void escriure_compatibles(const vector<char>& species, const vector<string>& compatible, const Matrix& matriu) {
    int n = species.size();
    vector<int> sol;
    vector<bool> usat(n, false);

    escriure_compatibles(species, compatible, usat, sol, matriu);
}

int main() {
    int n;
    cin >> n;
    vector<char> species(n);
    Matrix matriu(n, vector<bool>(n, false));
    map<char,int> char2i;
    for (int i = 0; i < n; ++i) {
        cin >> species[i];
        char2i[species[i]] = i;
    }
    int m;
    string str;
    cin >> m;
    vector<string> compatible(m);
    for (int ii = 0; ii < m; ++ii) {
        cin >> str;
        matriu[char2i[str[0]]][char2i[str[1]]] = true;
        matriu[char2i[str[1]]][char2i[str[0]]] = true;
    }
    escriure_compatibles(species, compatible, matriu);
}
