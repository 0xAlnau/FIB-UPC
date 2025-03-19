#include<iostream>
#include<vector>
using namespace std;

void write_DNA(int n, vector<char>& lletres, vector<char>& sol) {
    if (sol.size() == n) {
        for (int i = 0; i < n; ++i) cout << sol[i];
        cout << endl;
    }
    else {
        for (int i = 0; i < 4; ++i) {
            sol.push_back(lletres[i]);
            write_DNA(n, lletres, sol);
            sol.pop_back();
        }
    }
}

void write_DNA(int n, vector<char>& lletres) {
    vector<char> sol;
    vector<bool> used(4, false);
    write_DNA(n, lletres, sol);
}

int main() {
    int n;
    cin >> n;
    vector<char> lletres = {'A', 'C', 'G', 'T'};
    write_DNA(n, lletres);
}
