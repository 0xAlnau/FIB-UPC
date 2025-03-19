#include<iostream>
#include<vector>
using namespace std;

void print_perm(int n, vector<int>& sol, vector<bool>& used) {
    if (sol.size() == n) {
        cout << "(";
        for (int i = 0; i < n; ++i) cout << (i == 0 ? "" : ",") << sol[i];
        cout << ")" <<endl;
    }

    else {
        for (int i = 0; i < n; ++i) {
            if (not used[i]) {
                used[i] = true;
                sol.push_back(i+1);
                print_perm(n, sol, used);
                used[i] = false;
                sol.pop_back();
            }
        }
    }
}

void print_perm(int n) {
    vector<int> sol;
    vector<bool> used(n, false);
    print_perm(n, sol, used);
}

int main() {
    int n;
    cin >> n;
    print_perm(n);
}
