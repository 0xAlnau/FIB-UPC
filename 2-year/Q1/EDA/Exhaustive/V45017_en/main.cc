#include<iostream>
#include<vector>
using namespace std;

int count_ways(int n, const vector<int>& v, vector<bool>& used, int sl, int sr, int st) {
    int resultat = 0;
    if (sr > sl) resultat = 0;
    else if (st == sr + sl) resultat = 1;
    else {
        for (int i = 0; i < n; ++i) {
            if (not used[i]) {
                used[i] = true;
                resultat += count_ways(n, v, used, sl+v[i], sr, st);
                resultat += count_ways(n, v, used, sl, sr+v[i],st);
                used[i] = false;
            }
        }
    }
    return resultat;
}

void count_ways(int n, const vector<int>& v) {
    int sum_left = 0;
    int sum_right = 0;
    int sum_total = 0;
    vector<bool> used(n, false);
    for (int x : v) sum_total += x;
    cout << count_ways(n, v, used, sum_left, sum_right, sum_total) << endl;
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> weights(n);
        for (int i = 0; i < n; ++i) cin >> weights[i];
        count_ways(n, weights);
    }
}
