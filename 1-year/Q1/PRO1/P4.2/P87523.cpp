//el programa leera una secuencia de letras, y
//dira si se encuentra la expresion "hello", de lo
//contrarios dira "bye"
//input: secuencia de caracteres acabada en '.'
//output: hello en casa de encontrar el patron
//deseado, y bye en el caso contrario
#include<iostream>
using namespace std;
int main () {
    char letra, a, b, c, d;
    bool found = false;
    cin >> a >> b >> c >> d;
    while (not found and cin >> letra and letra !='.'){

            if (a == 'h' and b == 'e' and c == 'l' and d == 'l' and letra == 'o') {
                found = true;
            }
            a = b; b = c; c = d; d = letra;

    }
    if (found) { cout << "hello" <<endl;}
    else { cout << "bye" <<endl;}
}
