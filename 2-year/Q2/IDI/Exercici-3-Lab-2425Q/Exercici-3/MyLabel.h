#include <QLabel>
#include <QKeyEvent> //nou
#include <QDebug>
class MyLabel: public QLabel
{
    Q_OBJECT // IMPORTANT

    bool encriptacio = true; // comencem estant encriptant
    int n = 1; // offset o n comença sent 1
    QString text_original;

    public:
        MyLabel(QWidget *parent);

        void keyPressEvent(QKeyEvent* e) override;

    public slots: // IMPORTANT

        void set_n(int value);

        void reseteja();

        void encripta(bool pressed);

        void desencripta(bool pressed);

        void tracta_text(QString s);

    signals: // IMPORTANT
        void envia_n(int n);

        void envia_estat(QString s);

        void envia_encripta();

        void envia_desencripta();

        void envia_buit(QString s);

        void tanca();
};
