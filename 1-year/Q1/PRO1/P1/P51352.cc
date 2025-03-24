#include<iostream>
using namespace std;

int main(){
    char elemento1, elemento2;
    cin >> elemento1 >> elemento2;

    if (elemento1 == 'V') {
        if (elemento2 == 'A') cout << 1 << endl;
        else if (elemento2 == 'P') cout << 2 << endl;
        else cout << "-" << endl;
    }

    else if (elemento1 == 'A') {
        if (elemento2 == 'P') cout << 1 << endl;
        else if (elemento2 == 'V') cout << 2 << endl;
        else cout << "-" << endl;
    }

    else if (elemento1 == 'P') {
        if (elemento2 == 'V') cout << 1 << endl;
        else if (elemento2 == 'A') cout << 2 << endl;
        else cout << "-" << endl;
    }
}
