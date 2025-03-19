/*Permutacions
Plantejar:
1.Quina estructura puc fer servir?
2.Quin serà la forma de fer la solució?
3.Li pasarem la solució parcial a una funció recursiva
4.Definir cas base,
5.On guardem totes les solucions? A un vector
6.Vector de bool per mirar si un nombre ja hi és
7.Itentar no usar maps i indicar solucions amb els indexos i no strings
*/

#include<iostream>
#include<vector>
using namespace std;

void escriu_permutacions(const vector<string>& p, vector<int>& sol, vector<bool>& usat) {
    int n = p.size();
    if (sol.size() == n) {
        cout <<"(";
        for (int i = 0; i < n; ++i) cout << (i == 0 ? "" : ",") << p[sol[i]];
        cout << ")" << endl;
    }
    else {
        for (int i = 0; i < n; ++i) {
            if (not usat[i]) {
                sol.push_back(i);
                usat[i] = true;
                escriu_permutacions(p, sol, usat);

                sol.pop_back(); //desactualitzar!!!
                usat[i] = false;
            }
        }
    }
}

void escriu_permutacions(const vector<string>& p) {
    //construeixo solució parcial inicial
    vector<int> sol; //no guardo les paraules, sino el index
    vector<bool> usat(p.size(), false);
    escriu_permutacions(p, sol, usat);
}

int main() {
    int n;
    cin >> n;
    vector<string> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    escriu_permutacions(p);
}
