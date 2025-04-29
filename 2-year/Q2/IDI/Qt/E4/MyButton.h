#include <QPushButton>
#include <QtGlobal> //qrand i qsrand
#include <QTime> //per generar semilla

class MyButton: public QPushButton
{
    Q_OBJECT // IMPORTANT

     bool majus = false;
     QString aux;

    public:
        MyButton(QWidget *parent);

    public slots: // IMPORTANT

        void reb_majus(); //posa maju a true o false

        void a();

        void e();

        void i();

        void o();

        void u();

    signals: // IMPORTANT

        void envia_lletra(QString s);

};
