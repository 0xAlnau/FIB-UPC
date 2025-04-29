#include <QLabel>
#include <QKeyEvent> //nou
class MyLabel: public QLabel
{
    Q_OBJECT // IMPORTANT

    public:
        MyLabel(QWidget *parent);

        bool nom_b = false; //es posen a true si la tenim
        bool cognom_b = false;
        bool dni_b = false;

        QString nom;
        QString cognom;
        QString dni;
        QString data;
        QString adreca;
        QString codi;
        QString nacionalitat;

    public slots: // IMPORTANT

        void reinicia();

        void activa_formulari();

        void rep_nom(QString s);

        void rep_cognom(QString s);

        void rep_DNI(QString s);

        void rep_data(QString s);

        void rep_adreca(QString s);

        void rep_codi(QString s);

        void rep_nacionalitat(QString s);

    signals: // IMPORTANT

};
