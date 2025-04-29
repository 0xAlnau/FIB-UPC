#include "MyLabel.h"
//canviar el .pro!!

// constructor
MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots
void MyLabel::reinicia() {
    nom_b = false;
    cognom_b = false;
    dni_b = false;

    nom = "";
    cognom = "";
    dni = "";
    data = "";
    adreca = "";
    codi = "";
    nacionalitat = "";

    setText("");
}

void MyLabel::activa_formulari() {
    if (nom_b and cognom_b and dni_b) {
        QString aux = nom + " + " + cognom + " + " + dni;

        if (data != "") aux += " + " + data;
        if (adreca != "") aux += " + " + adreca;
        if (codi != "") aux += " + " + codi;
        if (nacionalitat != "") aux += " + " + nacionalitat;

        setText(aux);
    }
    else {
        setText("Els camps 'nom', 'cognom' i 'DNI' són obligatoris!");
    }
}

void MyLabel::rep_nom(QString s) {
    nom = s;
    if (s != "") nom_b = true;
    else nom_b = false;
}

void MyLabel::rep_cognom(QString s) {
    cognom = s;
    if (s != "") cognom_b = true;
    else cognom_b = false;
}

void MyLabel::rep_DNI(QString s) {
    dni = s;
    if (s != "") dni_b = true;
    else dni_b = false;
}

void MyLabel::rep_data(QString s) {
    data = s;
}

void MyLabel::rep_adreca(QString s) {
    adreca = s;
}

void MyLabel::rep_codi(QString s) {
    codi = s;
}

void MyLabel::rep_nacionalitat(QString s) {
    nacionalitat = s;
}



