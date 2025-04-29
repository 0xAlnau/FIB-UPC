#include "MyButton.h"
//canviar el .pro!!

// constructor
MyButton::MyButton(QWidget *parent)
    : QPushButton(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots
void MyButton::reb_majus() { //posa maju a true o false
    if (majus) majus = false;
    else majus = true;
}

void MyButton::a() {
    if (majus) {
        aux = "A";
        emit envia_lletra(aux);
    }
    else {
        aux = "a";
        emit envia_lletra(aux);
    }
}

void MyButton::e() {
    if (majus) {
        aux = "E";
        emit envia_lletra(aux);
    }
    else {
        aux = "e";
        emit envia_lletra(aux);
    }
}

void MyButton::i() {
    if (majus) {
        aux = "I";
        emit envia_lletra(aux);
    }
    else {
        aux = "i";
        emit envia_lletra(aux);
    }
}

void MyButton::o() {
    if (majus) {
        aux = "O";
        emit envia_lletra(aux);
    }
    else {
        aux = "o";
        emit envia_lletra(aux);
    }
}

void MyButton::u() {
    if (majus) {
        aux = "U";
        emit envia_lletra(aux);
    }
    else {
        aux = "u";
        emit envia_lletra(aux);
    }
}

