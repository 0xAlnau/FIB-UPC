#include <QLabel>
#include <QKeyEvent> //nou
class MyLabel: public QLabel
{
    Q_OBJECT // IMPORTANT

    int R = 0;
    int G = 0;
    int B = 0;

    public:
        MyLabel(QWidget *parent);

    public slots: // IMPORTANT

    void rep_R(int valor);

    void rep_G(int valor);

    void rep_B(int valor);

    signals: // IMPORTANT

    void envia_color(int v, int v2, int v3);
};
