#include<iostream>
using namespace std;

int main(){
    int base, number;
    while (cin >> base >> number) {
        int contador = 0;
        while (number != 0) {
            number = number / base;
            ++contador;
        }
        cout << contador << endl;
    }
}
