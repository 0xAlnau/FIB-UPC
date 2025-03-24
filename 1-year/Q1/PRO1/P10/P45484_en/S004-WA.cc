#include <iostream>
#include <vector>
using namespace std;

bool magic_square(const vector<vector<int>>& M) {
    bool is_magic = true;
    int n = M[0].size();
    int first_diagonal = 0, second_diagonal = 0;
    vector<int> columnes(n, 0);
    vector<int> files(n, 0);
    int n2 = n-1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            columnes[j] += M[i][j];
            files[i] += M[i][j];
            if (i == j) first_diagonal += M[i][j];
            if (n2 == j) {
                second_diagonal += M[i][j];
                --n2;
            }
        }
    }

    for (int k = 0; is_magic and k < n; ++k) {
        if (columnes[k] == files[k]) {}
        else is_magic = false;
    }

    if (is_magic and first_diagonal == second_diagonal and first_diagonal == columnes[0]) {}
    else is_magic = false;
    return is_magic;
}

int main() {
    int n;
    while (cin >> n) {
        vector<vector<int>> M(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> M[i][j];
            }
        }
        cout << magic_square(M) << endl;
    }
}
