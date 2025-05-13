#include "MyLabel.h"
//canviar el .pro!!

// constructor
MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent) {
    // Inicialització d'atributs si cal
    setFocusPolicy(Qt::StrongFocus); // permet fer servir les tecles!
}

// implementació slots
void MyLabel::set_n(int value) {
    n = value;
    tracta_text(text_original);
}

void MyLabel::reseteja() {
    text_original = "";
    n = 1;
    encriptacio = true;
    emit envia_encripta();
    emit envia_n(1);
    emit envia_buit("");
    emit envia_estat("Text encriptat:");
    tracta_text(text_original);
}

void MyLabel::encripta(bool pressed) {
    if (pressed) {
        encriptacio = true;
        emit envia_estat("Text encriptat:");
        tracta_text(text_original);
    }
}

void MyLabel::desencripta(bool pressed) {
    if (pressed) {
        encriptacio = false;
        emit envia_estat("Text desencriptat:");
        tracta_text(text_original);
    }
}

void MyLabel::tracta_text(QString s) {
    text_original = s;
    if (encriptacio) {
        QString aux = s;
        int size = s.length();
        for (int i = 0; i < size; ++i) {
            aux[i] = aux[i].unicode() + n; //unicode per pasar a numero el QChar
        }
        setText(aux);
    }
    else setText(s);

}

//signal
void MyLabel::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_1) {
        n = 1;
        emit envia_n(1);
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_2) {
        n = 2;
        emit envia_n(2);
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_3) {
        n = 3;
        emit envia_n(3);
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_4) {
        n = 4;
        emit envia_n(4);
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_5) {
        n = 5;
        emit envia_n(5);
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_E) {
        encriptacio = true;
        emit envia_encripta();
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_D) {
        encriptacio = false;
        emit envia_desencripta();
        tracta_text(text_original);
    }
    else if (e->key() == Qt::Key_S && (e->modifiers() & Qt::AltModifier)) {
        emit tanca();
    }
    else if (e->key() == Qt::Key_R && (e->modifiers() & Qt::AltModifier)) {
        reseteja();
    }
    else {
        QLabel::keyPressEvent(e);
    }
}


