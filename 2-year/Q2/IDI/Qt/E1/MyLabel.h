#include <QLabel>
#include <QKeyEvent> //nou
class MyLabel: public QLabel
{
    Q_OBJECT // IMPORTANT

    bool obert = true;

    int n_cotxes = 0;
    int n_motos = 0;
    int n_camions = 0;

    int recaptat = 0;

    public:
        MyLabel(QWidget *parent);

    public slots: // IMPORTANT

        void canviar_pas(bool pressed);

        void passa_cotxe();

        void passa_moto();

        void passa_camio();

    signals: // IMPORTANT
        void canvi_cotxes(QString s);

        void canvi_motos(QString s);

        void canvi_camions(QString s);

        void canvi_recaptat(QString s);
};
