#include <iostream>
#include <string>

using namespace std;
// Pre: 0 <= i <= j < s.size()
// Post: el substring s[i..j] s'ha revessat. La resta de s no ha canviat.
void reverseSubstring(string &s, int i, int j) {
    if (i >= j) {}
    else {
        char aux = s[i];
        s[i] = s[j];
        s[j] = aux;
        return reverseSubstring(s, i + 1, j - 1);
    }
}
//El programa principal, gracias a l'ajuda de la funcio
//reverseSubstring revertira un string i l'imprimira'
//Input: el programa principal llegira un string, i dos
//enters, que identifiquen al string s.
//Output: una linia amb el string s canviat
/*
int main()  {
    string s;
    int i, j;
    while (cin >> s >> i >> j) {
        reverseSubstring(s, i, j);
        cout << s << endl;
    }
}
*/
