#include <iostream>
#include <vector>
using namespace std;

bool bin_search(double x, const vector<double>& v, int esq, int dret) {
    if (esq > dret) return false;
    else {
        int m = (esq+dret) / 2;

        if (v[m] == x) return true;
        else if (v[m] > x) {

        }

        else { //v[m] < x

        }
}

bool resistant_search(double x, const vector<double>& v) {
    int esq = 0;
    int dret = v.size()-1;
    return bin_search(x,v,esq,dret);
}


int main() {
    int n;
    while (cin >> n) {
        vector<double> V(n);
        for (int i = 0; i < n; ++i) cin >> V[i];
        int t;
        cin >> t;
        while (t--) {
            double x;
            cin >> x;
            cout << resistant_search(x, V) << endl;
        }
    }
}
