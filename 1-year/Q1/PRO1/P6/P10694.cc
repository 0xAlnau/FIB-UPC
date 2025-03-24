#include<iostream>
using namespace std;

void asteriscos(int n) {
    if (n == 0) {cout <<endl;}
    else {
        cout <<"*";
        asteriscos(n - 1);
    }
}

void rombos (int n) {
    if (n == 0) {}
    else {
        rombos(n-1);
        rombos(n-1);
        asteriscos (n);

    }
}

int main(){
    int n;
    while (cin >> n) {
        rombos (n);
    }

}
