#include "MyLabel.h"
//canviar el .pro!!

// constructor
MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent) {
    // Inicialització d'atributs si cal
}

// implementació slots
    void MyLabel::canviar_pas(bool pressed) {
        if (obert and pressed) {
            QString t = "Pas tancat";
            setText(t);

            QString c = "background-color: red;";
            setStyleSheet(c);

            obert = false;
        }
        else if (not obert and pressed) {
            QString t = "Pas obert";
            setText(t);

            QString c = "background-color: green;";
            setStyleSheet(c);

            obert = true;
        }
    }

    void MyLabel::passa_cotxe() {
        if (obert) {
            ++n_cotxes;
            recaptat += 1;

            char s[256];
            QString sq;

            sprintf(s, "Han passat: %d cotxes", n_cotxes);
            sq = QString::fromUtf8(s);

            emit canvi_cotxes(sq);

            sprintf(s, "S'ha recaptat: %d €", recaptat);
            sq = QString::fromUtf8(s);

            emit canvi_recaptat(sq);
        }
    }

    void MyLabel::passa_moto() {
        if (obert) {
            ++n_motos;
            recaptat += 1;

            char s[256];
            QString sq;

            sprintf(s, "Han passat: %d motos", n_motos);
            sq = QString::fromUtf8(s);

            emit canvi_motos(sq);

            sprintf(s, "S'ha recaptat: %d €", recaptat);
            sq = QString::fromUtf8(s);

            emit canvi_recaptat(sq);
        }
    }

    void MyLabel::passa_camio() {
        if (obert) {
            ++n_camions;
            recaptat += 4;

            char s[256];
            QString sq;

            sprintf(s, "Han passat: %d camions", n_camions);
            sq = QString::fromUtf8(s);

            emit canvi_camions(sq);

            sprintf(s, "S'ha recaptat: %d €", recaptat);
            sq = QString::fromUtf8(s);

            emit canvi_recaptat(sq);
        }
    }


//signal



