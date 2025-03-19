#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

void printqueue(queue<string>& q) {
    while (!q.empty()) {
        cout << " " << q.front();
        q.pop();
    }
}

void printqueuedep(queue<string>& q) {
    while (!q.empty()) {
        cout << q.front() << endl;
        q.pop();
    }
}

int main() {
    int n_cuas;
    cin >> n_cuas;
    cin.ignore(); // Ignorar el salto de línea después de leer n_cuas
    vector<queue<string>> cuas(n_cuas + 1);

    // Leer contenido inicial de las colas
    for (int i = 0; i < n_cuas + 1; ++i) {
        string s;
        getline(cin, s);
        stringstream m(s);
        string p;
        while (m >> p) {
            cuas[i].push(p);
        }
    }

    string operand;
    queue<string> depart;
    while (cin >> operand) {
        if (operand == "ENTERS") {
            string nou_nom;
            int cua;
            cin >> nou_nom >> cua;
            if (cua > 0 && cua <= n_cuas) {
                cuas[cua].push(nou_nom);
            }
        } else if (operand == "EXITS") {
            int cua;
            cin >> cua;
            if (cua > 0 && cua <= n_cuas && !cuas[cua].empty()) {
                depart.push(cuas[cua].front());
                cuas[cua].pop();
            }
        }
    }

    // Imprimir salidas
    cout << "DEPARTS" << endl;
    cout << "-------" << endl;
    printqueuedep(depart);
    cout << endl;

    // Imprimir contenido final de las colas
    cout << "FINAL CONTENTS" << endl;
    cout << "--------------" << endl;
    for (int j = 1; j <= n_cuas; ++j) {
        cout << "queue " << j << ":";
        printqueue(cuas[j]);
        cout << endl;
    }

    return 0;
}

