#include <iostream>
#include <string>
using namespace std;

//esta funcion se encargara de decir si una palabra
//es palindorma o no
//Pre: un string
//Post: un booleano
bool is_palindrome(const string& s) {
    int mida = s.length();
    bool diferent = false;
    for (int i = 0; not diferent and i < mida / 2; ++i) {
        if (s[i] == s[mida -1 -i]) {}
        else {
            diferent = true;
        }
    }
    if (diferent) { return false;}
    else {return true;}
}

int main() {
    string s;
    while (cin >> s) {
      cout << is_palindrome(s) << endl;
    }
}




