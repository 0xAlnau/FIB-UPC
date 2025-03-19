#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int num_options_change(int x, const vector<int>& v, vector<bool>& used, int sum_act, int sum_res, int u) {
    int n = v.size();
    int resultat = 0;
    if (sum_act == x) resultat = 1;
    else if (u == n) resultat = 0;
    else if (sum_act > x) resultat = 0;
    else if (sum_act + sum_res < x) resultat = 0;
    else {
        for (int i = u; i < n; ++i) {
            if (not used[i]) {
                used[i] = true;
                resultat += num_options_change(x, v, used, sum_act+v[i], sum_res-2*v[i], i+1);

                resultat += num_options_change(x, v, used, sum_act+2*v[i], sum_res-2*v[i], i+1);
                used[i] = false;
            }
        }
    }
    return resultat;
}

void num_options_change(int x, const vector<int>& v, int tot) {
    int n = v.size();
    vector<bool> used(n, false);
    int u = 0;
    int sum_act = 0;
    cout << num_options_change(x, v, used, sum_act, tot, u) << endl;
}

int main() {
    int x, n_monedes;
    while (cin >> x >> n_monedes) {
        vector<int> monedes(n_monedes);
        int value;
        int tot = 0;
        for (int i = 0; i < n_monedes; ++i) {
            cin >> value;
            monedes[i] = value;
            tot += value * 2;
        }
        //sort(monedes.begin(), monedes.end());
        num_options_change(x, monedes, tot);
    }
}
