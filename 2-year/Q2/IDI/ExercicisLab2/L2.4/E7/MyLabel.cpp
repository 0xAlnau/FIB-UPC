#include "MyLabel.h"
//canviar el .pro!!

// constructor
MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots

void MyLabel::rep_R(int valor) {
    R = valor;

    char buff[256];
    sprintf(buff, "background-color:rgb(%d, %d, %d);", R, G, B);
    QString c = QString::fromUtf8(buff);

    setStyleSheet(c);

    emit envia_color(R,G,B);
}

void MyLabel::rep_G(int valor) {
    G = valor;

    char buff[256];
    sprintf(buff, "background-color:rgb(%d, %d, %d);", R, G, B);
    QString c = QString::fromUtf8(buff);

    setStyleSheet(c);

    emit envia_color(R,G,B);
}

void MyLabel::rep_B(int valor) {
    B = valor;

    char buff[256];
    sprintf(buff, "background-color:rgb(%d, %d, %d);", R, G, B);
    QString c = QString::fromUtf8(buff);

    setStyleSheet(c);

    emit envia_color(R,G,B);
}



