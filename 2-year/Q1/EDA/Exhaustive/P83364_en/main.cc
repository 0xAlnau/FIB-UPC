#include<iostream>
#include<vector>
using namespace std;

bool factible(int num, const vector<int>& v) {
    for (int x : v) if (num % x == 0) return false;
    return true;
}

void print_nums(const vector<int>& v, int num, int dig, int act_dig) {
    if (dig == act_dig) cout << num << endl;
    else {
        num *= 10; //afegim digit
        for (int i = 0; i < 10; ++i) {
            num += i;
            if (factible(num, v)) print_nums(v, num, dig, act_dig+1);
            num -= i;
        }
    }
}

void print_nums(int n, const vector<int>& v) {
    print_nums(v, 0, n, 0);
    cout << "----------" << endl;
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        int divisor;
        vector<int> divisors;
        for (int i = 0; i < m; ++i) {
            cin >> divisor;
            divisors.push_back(divisor);
        }
        print_nums(n, divisors);
    }
}
