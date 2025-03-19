#include<iostream>
using namespace std;

int pwr(int x, int exp, int mod) {
    if (exp == 0) return 1 % mod;
    else {
        int mult = pwr(x,exp/2,mod);

        if (exp % 2 == 0) return (1LL * mult*mult) % mod;

        else return (1LL * mult*mult*x) % mod;
    }
}

int main() {
    int x, exp, mod;
    while (cin >> x >> exp >> mod) {
        cout << pwr(x, exp, mod) % mod << endl;
    }
}
