#include<iostream>
#include<vector>
using namespace std;

void uns_i_zeros(vector<int>& sol, int n) {
    if (n == sol.size()) {
        for (int i = 0; i < n; ++i) cout << (i == 0 ? "" : " ") << sol[i];
        cout << endl;
    }

    else {
        sol.push_back(0);
        uns_i_zeros(sol, n);

        sol.pop_back();

        sol.push_back(1);
        uns_i_zeros(sol, n);

        sol.pop_back();
    }
}

void uns_i_zeros(int n) {
    vector<int> sol;
    uns_i_zeros(sol, n);
}

int main() {
    int n;
    cin >> n;
    uns_i_zeros(n);
}
