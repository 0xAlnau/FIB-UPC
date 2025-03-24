#include <iostream>
#include <typeinfo>
using namespace std;

struct Clock {
    int h;
    int m;
    int s;
};
//esta accion se encarga de poner un struct
//de enteros a zeros
//Post: un struct con horas, minutos y segundo a zero
Clock midnight() {
    Clock rellotge;
    rellotge.h = 0;
    rellotge.m = 0;
    rellotge.s = 0;
    return rellotge;
}
//esta accion incrementara en 1 los segundos de
//un reloj, y si hace falta tambien cambiara minutos
//u horas
//Pre: un struct con enteros
void increase(Clock& r) {
    ++r.s;
    if (r.s == 60) {
        r.s = 0;
        ++r.m;
    }
    if (r.m == 60) {
        r.m = 0;
        ++r.h;
    }
    if (r.h == 24) {
        r.h = 0;
    }
}
//esta accion imprimira linias del tiempo de un reloj
//en el formato HH:MM:SS
//Pre: un struct de enteros
//Post: un linia de la hora
void print(const Clock& r) {
    cout << r.h / 10 << r.h % 10 <<":"<< r.m / 10 << r.m % 10 <<":"<< r.s / 10 << r.s % 10 <<endl;
}

