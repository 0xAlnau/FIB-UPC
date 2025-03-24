//el programa leera una secuencia de caracteres, dira
//cuantas "a" hay en la secuencia antes del primer punto
//input: secuencias de caracteres con al menos un punto
//output: el numero de "a" que salen antes del primer periodo

#include<iostream>
using namespace std;
int main () {
    char letras;
    int total = 0;
    bool a = false;
    while (not a){

        cin >> letras;
        while (letras != '.') {
            if(letras == 'a') { ++total; }
            cin >> letras;
        }
    a = true;
    cout << total <<endl;
    }
}
