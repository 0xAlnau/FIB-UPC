#include<iostream>
#include<typeinfo>
using namespace std;
struct Time {
    int hour, minute, second;
};

//esta accion incrementara en 1 los segundos de
//un reloj, y si hace falta tambien cambiara minutos
//u horas
//Pre: un struct con enteros
//Post: una linia con la hora
void increase(Time& r){
    ++r.second;
    if (r.second == 60) {
        r.second = 0;
        ++r.minute;
        if (r.minute == 60) {
        r.minute = 0;
        ++r.hour;
            if (r.hour == 24) {
                r.hour = 0;
            }
        }
    }

    cout << r.hour << " " << r.minute << " " << r.second <<endl;
}

//esta accion decrementara en 1 los segundos de
//un reloj, y si hace falta tambien cambiara minutos
//u horas
//Pre: un struct con enteros
//Post: una linia con la hora
void decrease(Time& r){
    --r.second;
    if (r.second < 0) {
        r.second = 59;
        --r.minute;
        if (r.minute < 0) {
            r.minute = 59;
            --r.hour;
            if (r.hour < 0) {
            r.hour = 23;
            }
        }
    }
    cout << r.hour << " " << r.minute << " " << r.second <<endl;
}
//incrementa y decrementa una hora
void one_second(const Time& t, Time& t1, Time& t2) {
    increase(t1);
    t1 = t;
    decrease(t2);
}

int main(){
    int h, m, s;
    Time reloj;
    while (cin >> h >> m >> s) {
        reloj.hour = h;
        reloj.minute = m;
        reloj.second = s;
        Time reloj2 = reloj;
        Time reloj3 = reloj;
        one_second(reloj,reloj2,reloj3);
    }
}
