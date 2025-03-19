#include<iostream>
#include<vector>
using namespace std;

void write_lol(int n, int m, vector<vector<char>>& v) {

}

int main(){
    int n, m;
    while (cin >> n >> m) {
        vector<vector<char>> lols(n, vector<char>(m));
        write_lol(n, m, lols);
    }
}
