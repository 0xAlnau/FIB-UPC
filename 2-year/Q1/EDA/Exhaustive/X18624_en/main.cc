#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool is_vowel(char c) {
    return c == 'a' or c == 'e' or c == 'i' or c == 'o' or c =='u';
}

void words(int n, const vector<char>& v, vector<char>& sol, int index) {
    if (sol.size() == n) {
        for (char c : sol) cout << c;
        cout << endl;
    }
    else {
        int size = sol.size() +1; // +1 pel push_back
        for (char c : v) {
            sol.push_back(c);

            if (size > 1 and is_vowel(sol[size-1]) and is_vowel(sol[size-2])) {}
            else words(n, v, sol, index);

            sol.pop_back();
        }
    }
}

void words(int n, const vector<char>& v) {
    vector<char> sol;
    words(n, v, sol, 0);
    cout << "----------" << endl;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<char> lletres(m);
        for (int i = 0; i < m; ++i) cin >> lletres[i];
        sort(lletres.begin(), lletres.end());
        words(n, lletres);
    }
}
