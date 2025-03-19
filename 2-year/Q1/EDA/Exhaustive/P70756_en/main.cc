#include<iostream>
#include<vector>
using namespace std;

void write_subsets(vector<string>& v, int p,) {

}

void write_subsets(vector<string>& v, int p) {
    vector<char> sol; //anira guardant els indexos de v
    vector<bool> used(v.size(), false); //per veure quins hem usat

    write_subsets(v, p, sol, used, 0);
}

int main() {
    int n;
    cin >> n;
    vector<string> paraules(n);

    for (int i = 0; i < n; ++i) cin >> paraules[i];

    int p;
    cin >> p;

    write_subsets(paraules, p);
}
