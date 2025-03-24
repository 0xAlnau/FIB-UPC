#include<iostream>
using namespace std;

int main (){
    int number;
    int contador = 0;
    cin >> number;
    while (number >= 0) {
        number = number / 10;
        ++contador;
    }
    cout << contador << endl;
}

