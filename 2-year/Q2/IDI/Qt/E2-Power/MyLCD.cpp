#include "MyLCD.h"
//canviar el .pro!!

// constructor
MyLCD::MyLCD(QWidget *parent)
    : QLCDNumber(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots
    void MyLCD::setZero() {
        display(0);
        QString c = "color: green;"; //background-color: black;
        setStyleSheet(c);
    }

    void MyLCD::canviNum(int n) {
        display(n);
        if (n == 0) { //zero
            QString c = "color: green;"; //background-color: black;
            setStyleSheet(c);
        }
        else if (n % 2 == 0) { //parell
            QString c = "color: blue;"; //background-color: black;
            setStyleSheet(c);
        }
        else { // imparell
            QString c = "color: red;"; //background-color: black;
            setStyleSheet(c);
        }
    }

//signal



