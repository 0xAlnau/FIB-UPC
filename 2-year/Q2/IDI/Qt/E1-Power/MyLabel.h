#include <QLabel>
#include <QKeyEvent> //nou
class MyLabel: public QLabel
{
    Q_OBJECT // IMPORTANT

    int llargada = 0;

    public:
        MyLabel(QWidget *parent);

    public slots: // IMPORTANT
        void canviText();

        void setNum(int n);

    signals: // IMPORTANT

};
