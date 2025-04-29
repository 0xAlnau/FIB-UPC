#include <QLCDNumber>
#include <QKeyEvent> //nou
class MyLCD: public QLCDNumber
{
    Q_OBJECT // IMPORTANT

    public:
        MyLCD(QWidget *parent);

    public slots: // IMPORTANT

        void setZero();

        void canviNum(int n);

    signals: // IMPORTANT

};
