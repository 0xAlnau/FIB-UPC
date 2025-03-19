#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<char>> MC;

const vector<char> lletres1 = {'A', 'C', 'G', 'T'};
const vector<char> lletres2 = {'T', 'G', 'C', 'A'};
bool imposible = false;

bool comprova(MC& M, int index) {
    if (M[0][index] == 'A') {
        if (M[1][index] == 'A' or M[1][index] == 'C' or M[1][index] == 'G') return true;
    }

    else if (M[0][index] == 'C') {
        if (M[1][index] == 'C' or M[1][index] == 'A' or M[1][index] == 'T') return true;
    }

    else if (M[0][index] == 'G') {
        if (M[1][index] == 'G' or M[1][index] == 'A' or M[1][index] == 'T') return true;
    }

    else { // T
        if (M[1][index] == 'T' or M[1][index] == 'C' or M[1][index] == 'G') return true;
    }
    return false;
}

void write_adn(MC& M, int index) {
    int m = M[0].size();
    if (index == m) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j == m-1) cout << M[i][j];
                else cout << M[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
    else {
        if (M[0][index] == '.' and M[1][index] == '.') {
            for (int i = 0; i < 4; ++i) {
                M[0][index] = lletres1[i];
                M[1][index] = lletres2[i];
                write_adn(M, index+1);
                M[0][index] = '.';
                M[1][index] = '.';
            }
        }
        else if (M[0][index] == 'A' and M[1][index] == '.') {
            M[1][index] = 'T';
            write_adn(M, index+1);
            M[1][index] = '.';
        }
        else if (M[0][index] == 'C' and M[1][index] == '.') {
            M[1][index] = 'G';
            write_adn(M, index+1);
            M[1][index] = '.';
        }
        else if (M[0][index] == 'G' and M[1][index] == '.') {
            M[1][index] = 'C';
            write_adn(M, index+1);
            M[1][index] = '.';
        }
        else if (M[0][index] == 'T' and M[1][index] == '.') {
            M[1][index] = 'A';
            write_adn(M, index+1);
            M[1][index] = '.';
        }
        else if (M[0][index] == '.' and M[1][index] == 'A') {
            M[0][index] = 'T';
            write_adn(M, index+1);
            M[0][index] = '.';
        }
        else if (M[0][index] == '.' and M[1][index] == 'C') {
            M[0][index] = 'G';
            write_adn(M, index+1);
            M[0][index] = '.';
        }
        else if (M[0][index] == '.' and M[1][index] == 'G') {
            M[0][index] = 'C';
            write_adn(M, index+1);
            M[0][index] = '.';
        }
        else if (M[0][index] == '.' and M[1][index] == 'T') {
            M[0][index] = 'A';
            write_adn(M, index+1);
            M[0][index] = '.';
        }
    }
}

void write_adn(MC& M) {
    if (not imposible) write_adn(M, 0);
    cout << "----------" << endl;
}

int main() {
    int n = 2;
    int m;
    while (cin >> m) {
        imposible = false;
        MC adn(n, vector<char>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> adn[i][j];
                if (i == 1 and adn[i][j] != '.') comprova(adn, j);
            }
        }
        write_adn(adn);
    }
}
