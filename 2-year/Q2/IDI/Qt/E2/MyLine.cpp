#include "MyLine.h"
//canviar el .pro!!

// constructor
MyLine::MyLine(QWidget *parent)
    : QLineEdit(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots

void MyLine::comprova_lletra(QString s) {
    if (errors != 5 and not trobada) {
        if (s == d[pos_actual] or s == d[pos_actual]) {
            paraula[pos_actual] = D[pos_actual];
            ++pos_actual;
            emit envia_text(paraula);
            if (pos_actual == 10) { //ja ha acabat
                trobada = true;
                QString s2;

                s2 = "background-color: green;";
                setStyleSheet(s2);

                s2 = "";
                setText(s2);
            }
        }
        else if (s != "") { //no volem que compti com error el borrar la lletra per posar una nova
            ++errors;
            emit envia_error(5 - errors);
            if (errors == 5) {
                QString s2;

                s2 = "background-color: red;";
                setStyleSheet(s2);

                s2 = "";
                setText(s2);
            }
        }
    }
}

void MyLine::reinicia() {
    errors = 0;
    emit envia_error(5);

    pos_actual = 0;
    QString s = "********";
    emit envia_text(s);

    s = "background-color: white;";
    setStyleSheet(s);

    s = "";
    setText(s);

    trobada = false;

    paraula = "**********";
}


