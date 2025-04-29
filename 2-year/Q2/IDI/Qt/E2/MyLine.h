#include <QLineEdit>
#include <QKeyEvent> //nou

//inputMask = A //nomes una lletra deixa
//inputMask = D //nomes deixa numeros

class MyLine: public QLineEdit
{
    Q_OBJECT // IMPORTANT

    QString d = "diccionari";
    QString D = "DICCIONARI";
    QString paraula = "**********";

    int pos_actual = 0; //indica en quina posicio de l'string estem
    int errors = 0; //indica el nombre d'errors fets

    bool trobada = false;

    public:
        MyLine(QWidget *parent);

    public slots: // IMPORTANT

        void comprova_lletra(QString s);

        void reinicia();

    signals: // IMPORTANT

        void envia_text(QString s);

        void envia_error(int error);
};
