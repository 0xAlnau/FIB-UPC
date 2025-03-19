#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool inferior(int num, string last) {
    string s = to_string(num);
    int length = last.length();
    if(length == 1) {
         return s < last;
     }
     else {
         last.pop_back();
         return s < last;
     }
}

void escriure_canvi(int x, const vector<int>& v, vector<pair<int, bool>>& sol, vector<bool>& used, int sum_act, int sum_res, int u) {
    int n = v.size();
    if (sum_act == x) {
        cout << x << " =";
        for (int i = 0; i < sol.size(); ++i) {
            if (i == 0) {
                if (sol[i].second) cout << " " << v[sol[i].first] << "p";
                else cout << " " << v[sol[i].first];
            }
            else {
                if (sol[i].second) cout << " + " << v[sol[i].first] << "p";
                else cout << " + " << v[sol[i].first];
            }
        }
        cout << endl;
    }
    if (u == n) return;
    if (sum_act > x) return;
    if (sum_act + sum_res < x) return;
    else {
        for(int i = u; i < n; ++i) {
            if ((((i % 2 == 0 or i == 0) and not used[i] and not used[i+1]) or (i % 2 != 0 and not used[i]))) {
                used[i] = true;
                if (i % 2 == 0 or i == 0) sol.push_back({i, false});
                else sol.push_back({i, true});
                escriure_canvi(x, v, sol, used, sum_act+v[i], sum_res-v[i], i+1);
                sol.pop_back();
                used[i] = false;
             }
        }
    }
}

void escriure_canvi(int x, const vector<int>& v) {
    int n = v.size();
    vector<bool> used(n, false);
    vector<pair<int,bool>> sol;
    int sum_act = 0;
    int sum_res = 0;
    for (int u : v) sum_res += u;
    int indx = 0;
    escriure_canvi(x, v, sol, used, sum_act, sum_res, indx);
    cout << "----------" << endl;
}

int main() {
    int x, n;
    while (cin >> x >> n) {
        vector<int> monedes(2*n);
        for (int i = 0; i < 2*n; i += 2) {
            cin >> monedes[i];
            monedes[i+1] = monedes[i];
        }
        sort(monedes.begin(), monedes.end());
        escriure_canvi(x, monedes);
    }
}
