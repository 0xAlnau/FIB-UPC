//este programa imprimira la cantidad total de segundos
//establecida en años, dias, horas, minutos y segundos
//input: cinco numeros naturales, se introduciran en orden de
//años hasta llegar a segundos (asumimos que cada año tiene 365 dias)
//output: la cantidad total de segundos

#include<iostream>
using namespace std;
int main () {
    int y, d, h, m, s;
    cin >> y >> d >> h >> m >> s;

    int sy= y * 365 * 24 * 3600;
    int sd= d * 24 * 3600;
    int sh= h * 3600;
    int sm= m * 60;

    int t= sy + sd + sh + sm +s;
    cout << t <<endl;
}
