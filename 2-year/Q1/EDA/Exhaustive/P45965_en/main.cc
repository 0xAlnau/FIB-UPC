#include<iostream>
#include<vector>
using namespace std;

void write_ones(int n, int uns, vector<int>& sol, int u) {
    if (u > uns) {} //ens pasem de uns
    else if (u + n - sol.size() < uns) {} //no caben mes
    else if (u == uns and n == sol.size()) {
        for (int i = 0; i < n; ++i) cout << (i == 0 ? "" : " ") << sol[i];
        cout << endl;
    }

    else {
        sol.push_back(0);
        write_ones(n, uns, sol, u);
        sol.pop_back();

        sol.push_back(1);
        ++u;
        write_ones(n, uns, sol, u);
        sol.pop_back();
        --u;
    }

}

void write_ones(int n, int uns) {
    vector<int> sol;
    write_ones(n, uns, sol, 0); //0 són els nombres de uns actuals
}

int main() {
    int n, uns;
    cin >> n >> uns;
    write_ones(n, uns);
}
