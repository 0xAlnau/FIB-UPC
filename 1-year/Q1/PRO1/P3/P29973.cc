#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    string star = "*";
    for (int i = 0; i < n; ++i) {
        cout << star << endl;
        star += "*";
    }
}
