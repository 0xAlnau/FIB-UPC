#include "MyButton.h"
//canviar el .pro!!

// constructor
MyButton::MyButton(QWidget *parent)
    : QPushButton(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots

void MyButton::genera_color() {
    qsrand(QTime::currentTime().msec()); //genera semilla
    color = qrand() % 4; //0 = rosa, 1 = verd, 2 = blau, 3 = negre

    if (color == 0) {
        QString s = "background-color: pink;";
        setStyleSheet(s);
    }
    else if (color == 1) {
        QString s = "background-color: green;";
        setStyleSheet(s);
    }
    else if (color == 2) {
        QString s = "background-color: blue;";
        setStyleSheet(s);
    }
    else {
        QString s = "background-color: black;";
        setStyleSheet(s);
    }
}

void MyButton::canvia_color(int n) { //jo ho fare de tal forma que la n no cal
    if (color == 0) {
        ++color;
        QString s = "background-color: black;";
        setStyleSheet(s);
    }
    else if (color == 1) {
        ++color;
        QString s = "background-color: blue;";
        setStyleSheet(s);
    }
    else if (color == 2) {
        ++color;
        QString s = "background-color: green;";
        setStyleSheet(s);
    }
    else {
        color = 0;
        QString s = "background-color: pink;";
        setStyleSheet(s);
    }
}


