#include <QLineEdit>

class MyLine: public QLineEdit
{
    Q_OBJECT // IMPORTANT


    public:
        MyLine(QWidget *parent);

    public slots: // IMPORTANT

        void afegeix_text(QString s);

    signals: // IMPORTANT


};
