#include<iostream>
#include<vector>
using namespace std;

void print_ways(vector<char>& sol, int end, bool pair, vector<int>& col, int s) {
    int n = sol.size();
    if (n == end and pair and col[0] == s and col[1] == s and col[2] == s) {
        for (char c : sol) cout << c;
        cout << endl;
    }
    else if (n < end) {
        ++n;
        for (int i = 1; i <= 3; ++i) {
            sol.push_back(i+'0');
            ++col[i-1];

            if (not pair and sol[n-1] == sol[n-2]) print_ways(sol, end, true, col, s);
            else if (pair and sol[n-1] == sol[n-2]) {}
            else if (pair and sol[n-1] != sol[n-2]) print_ways(sol, end, true, col, s);
            else if (not pair and sol[n-1] != sol[n-2]) print_ways(sol, end, false, col, s);

            --col[i-1];
            sol.pop_back();
        }
    }
}

void print_ways(int n) {
    vector<char> sol;
    vector<int> col(3, 0);
    int end = 3*n;

    sol.push_back('1');
    col[0] = 1;
    print_ways(sol, end, false, col, n);
    col[0] = 0;
    sol.pop_back();

    sol.push_back('2');
    col[1] = 1;
    print_ways(sol, end, false, col, n);
    col[1] = 0;
    sol.pop_back();

    sol.push_back('3');
    col[2] = 1;
    print_ways(sol, end, false, col, n);
    col[2] = 0;
    sol.pop_back();
    cout << "**********" << endl;
}

int main() {
    int n;
    while (cin >> n) {
        print_ways(n);
    }
}
