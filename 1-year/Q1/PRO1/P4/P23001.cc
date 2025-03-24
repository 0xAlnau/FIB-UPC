#include<iostream>
using namespace std;
int main() {
    string word;
    cin >> word;
    string words;
    int contador1 = 1;
    int contador2 = 1;
    while (cin >> words) {
        if (word == words) {
           if (contador1 != 1) ++contador1;
           else {
                ++contador1;
           }
        }
        else {
            if (contador1 > contador2) {
                contador2 = contador1;
            }
            contador1 = 0;
        }
    }
    cout << contador2 << endl;
}
