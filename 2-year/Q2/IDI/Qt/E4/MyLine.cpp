#include "MyLine.h"
//canviar el .pro!!

// constructor
MyLine::MyLine(QWidget *parent)
    : QLineEdit(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots

void MyLine::afegeix_text(QString s) {
    QString aux = text();
    aux += s;
    setText(aux);
}


