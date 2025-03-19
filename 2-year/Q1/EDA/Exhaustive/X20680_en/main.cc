#include<iostream>
#include<vector>
using namespace std;

const vector<char> lletres = {'x', 'y', 'z'};

void write_ways(int n, int c, vector<char>& sol, int cx, int cy, int cz) {
    if (sol.size() == n) {
        for (char x : sol) cout << x;
        cout << endl;
    }
    else {
        int size = sol.size() + 1;
        for (char x : lletres) {
            if (size <= 1) {
                sol.push_back(x);
                if (x == 'x') write_ways(n, c, sol, cx+1, cy, cz);
                else if (x == 'y') write_ways(n, c, sol, cx, cy+1, cz);
                else write_ways(n, c, sol, cx, cy, cz+1);
                sol.pop_back();
            }
            else {
                sol.push_back(x);
                if (x == 'x' and sol[size-2] != 'x') write_ways(n, c, sol, 1, 0, 0);
                else if (x == 'x' and sol[size-2] == 'x' and cx < c) write_ways(n, c, sol, cx+1, 0, 0);
                else if (x == 'y' and sol[size-2] != 'y') write_ways(n, c, sol, 0, 1, 0);
                else if (x == 'y' and sol[size-2] == 'y' and cy < c) write_ways(n, c, sol, 0, cy+1, 0);
                else if (x == 'z' and sol[size-2] != 'z') write_ways(n, c, sol, 0, 0, 1);
                else if (x == 'z' and sol[size-2] == 'z' and cz < c) write_ways(n, c, sol, 0, 0, cz+1);
                sol.pop_back();
            }
        }
    }
}

void write_ways(int n, int c) {
    int cx = 0;
    int cy = 0;
    int cz = 0;
    vector<char> sol;
    write_ways(n, c, sol, cx, cy, cz);
    cout << "--------------------" << endl;
}

int main() {
    int n;
    int c;
    while (cin >> n >> c) {
        write_ways(n, c);
    }
}
