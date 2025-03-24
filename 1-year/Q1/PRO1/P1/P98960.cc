//programa cambia de mayuscula a minuscula e inversa
//input: una letra
//output: la mayuscula o minuscula de esa letra
#include<iostream>
using namespace std;
int main () {
    char x;
    cin >> x;
    char v1= 'a' - 'A';
    if (x >= 'a' and x <= 'z') {
        char w= x - v1;
        cout << w <<endl;
        }
    else if (x >= 'A' and x <= 'Z'){
        char w= x + v1;
        cout << w <<endl;
        }
}
