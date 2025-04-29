#include "MyLabel.h"
//canviar el .pro!!

// constructor
MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots
void MyLabel::canviText() {
    QString t = text();
    t.truncate(llargada);
    setText(t);
}

void MyLabel::setNum(int n) {
    llargada = n;
    canviText();
}


//signal



