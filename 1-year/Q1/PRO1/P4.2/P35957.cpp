//en aquest programa juguen l'Anna i en Bernat, decideixen
//inventar-se n nombres, que han de tenir un nombre imparell de
//digits, i perd el primer que escrigui un nombre parell de digits,
//o bé, que el numero central del digit sigui igual a l'anterior.
//Sempre comença l'Anna. I el seu digit principal pot ser qualsevol.
//si pasan fins a 2n nombres i ningú ha perdut, hi ha empat.
//input: un nombre n que ens indica quants numeros posarà cadascu,
//i despres 2n nombres.
//output: A, si guanya Anna, B si guanaya Bernat, =, empat.
#include<iostream>
using namespace std;
int main () {
    int ns;
    bool anawin = false, estewin = false;
    cin >>ns;
    int numero, digitos = 0, guardar, medio, medio2;
        cin >> numero;
        guardar = numero;

        while (numero != 0) {
            numero = numero / 10;
            ++digitos;
        }

        if (digitos % 2 == 0) { estewin = true; }

        for (int j = 0; j < (digitos - 1) / 2; ++j) {
            guardar = guardar / 10;
        }
        medio = guardar % 10;
        cout << medio;
    cin >> numero;
    for (int i = 2; not anawin and not estewin and  i < 2 * ns; ++i) {
        digitos = 0;
        guardar = numero;
        while (numero != 0) {
            numero = numero / 10;
            ++digitos;
        }

        if (digitos % 2 == 0) {
            if (i % 2 == 0) { anawin = true; }
            else if (i % 2 != 0) { estewin = true; }
        }

        for (int j = 0; j < (digitos - 1) / 2; ++j) {
            guardar = guardar / 10;
        }
        medio2 = guardar % 10;
        cout << medio2;
        if (medio2 != medio) {
            if (i % 2 == 0) { anawin = true; }
            else if (i % 2 != 0) { estewin = true; }
        }
        cin >> numero;
    }

    if (anawin) { cout << "A" <<endl; }
    else if (estewin) { cout << "B" <<endl; }
    else { cout << "=" <<endl; }
}




