//el programa te dira si la letra que ha puesto el usuario es
//mayuscula o minuscula, y tambien si es una vocal o consonante
//input: una letra
//output: dos linias, en la primera si es mayuscula o minuscula
//y en la segunda linia vocal o consonante

#include<iostream>
using namespace std;
int main () {
    char a;
    cin >> a;

    if (a >= 'a' and a <= 'z') {
       if (a == 'a' or a == 'e' or a == 'i' or a == 'o' or a == 'u') {
           cout << "lowercase" <<endl;
           cout << "vowel" <<endl;
            }
       else {
           cout << "lowercase" <<endl;
           cout << "consonant" <<endl;
            }
    }
    else if (a >= 'A' and a <= 'Z') {
       if (a == 'A' or a == 'E' or a == 'I' or a == 'O' or a == 'U') {
           cout << "uppercase" <<endl;
           cout << "vowel" <<endl;
            }
       else {
           cout << "uppercase" <<endl;
           cout << "consonant" <<endl;
            }
    }

}
