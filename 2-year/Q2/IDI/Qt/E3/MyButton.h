#include <QPushButton>
#include <QtGlobal> //qrand i qsrand
#include <QTime> //per generar semilla

class MyButton: public QPushButton
{
    Q_OBJECT // IMPORTANT

    int color;

    public:
        MyButton(QWidget *parent);

    public slots: // IMPORTANT

        void genera_color();

        void canvia_color(int n);

    signals: // IMPORTANT

};
