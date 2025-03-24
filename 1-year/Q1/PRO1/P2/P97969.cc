//el programa leera cuantas 'a' hay
//input: secuencia acabada en punto
//output: numero de 'a'

#include<iostream>
#include<string>
using namespace std;
int main () {
    char p= 'x';
    int cont= 0;
    while (p != '.') {
        cin >> p;
        if(p == 'a') {cont= cont +1;}

    }

   cout << cont <<endl;


}
