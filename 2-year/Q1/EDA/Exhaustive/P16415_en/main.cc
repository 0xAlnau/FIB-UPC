#include<iostream>
#include<vector>
using namespace std;

int count_ways_queen(int n, vector<int>& t, int i, vector<int>& mc, vector<bool>& md1, vector<bool>& md2) {
    int resultat = 0;
    if (i == n) resultat = 1;
    else {
        for (int j = 0; j < n; ++j) { //j es la columna de la reina a la fila i
            if (not mc[j] and
                not md1[i+j] and
                not md2[i-j + n-1]) {
                t[i] = j;
                mc[j] = md1[i+j] = md2[i-j + n-1] = true;
                resultat += count_ways_queen(n, t, i+1, mc, md1, md2);
                mc[j] = md1[i+j] = md2[i-j + n-1] = false;
            }
        }
    }
    return resultat;
}

void count_ways_queen(int n) {
    vector<int> t(n); //reina a la fila i es a la columna j
    vector<int> mc(n, false); //si hi ha reina a la columna j
    vector<bool> md1(2*n-1, false); //els dos, per si ja hi ha reina a la diagonal i+j = k
    vector<bool> md2(2*n-1, false);
    int i = 0;
    cout << count_ways_queen(n, t, i, mc, md1, md2) << endl;;
}

int main() {
    int n;
    cin >> n;
    count_ways_queen(n);
}
