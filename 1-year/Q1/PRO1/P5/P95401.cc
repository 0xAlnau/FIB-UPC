//el programa dira si el año introducido es
//bisiesto o no.
//input: secuencias de numeros entre 1800 y 9999
//output: true o false
#include <iostream>
using namespace std;

bool is_leap_year(int year) {
    bool leap = false;
    if ( year % 4 == 0 and year % 400 ==0){ leap = true;}
    else if (year % 4 == 0){
        if (year % 10 == 0 and year % 100 == 0){leap = false;}
        else { leap = true; }
    }
    else{leap = false;}
    return leap;

}


int main()
{
    int a;
    while (cin >> a)
        cout << (is_leap_year(a) ? "true" : "false") << endl;

    return 0;
}
