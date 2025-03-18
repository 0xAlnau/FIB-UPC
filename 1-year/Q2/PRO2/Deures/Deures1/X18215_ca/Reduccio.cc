#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Aquesta funcio s'encarrega de comprovar de que si
   la part final del string traduccio coincideix amb
   una de totes les regles predefinides
   //Pre: dos strings, un amb la traduccio actual del
   programa, i un altre amb la regla a comprovar
   //Post: true si compleix la regla, false d'altra banda
   */
bool comprova(const string& traduccio, string regla){
    int size_traduccio = traduccio.length();
    int size_regla = regla.length();

    if (size_regla > size_traduccio) return false;

    int i = size_traduccio - 1;
    int j = size_regla - 1;
    while (j >= 0) {
        if (traduccio[i] != regla[j]) return false;
        --i;
        --j;
    }
    return true;
}

/* La seguent funcio serveix per esborrar els elements de un
   string i posar al final el char indicat per la regla adecuada
   Pre: un string amb la traduccio actual, un enter que indica fins
   on cal treure, y un char amb la lletra a posar per la regla
   Post: un push_back del valor char regla
 */
void canviar(string& traduccio, int treure, char regla){
    for (int i = 0; i < treure; ++i) {
        traduccio.pop_back();
    }

    traduccio.push_back(regla);
}

/* Aquest programa s'encarrega de traduir una instruccio donada,
   i traduira la instruccio segons unes regles donadas.
   Input: un string amb totes les instruccions de un programa,
   i que s'anira traduint segons les regles de més endavant.
   Output: un linia amb la instruccio donada reduida gracies a
   les regles.
 */
int main(){
    string programa;
    while (cin >> programa) {
        string traduccio;
        int size = programa.length();
        for (int i = 0; i < size; ++i) {
            traduccio.push_back(programa[i]);
            bool modificar = true;

            while (modificar) {
                modificar = false;

                //n ==> E
                if (comprova(traduccio, "n")) {
                    modificar = true;
                    canviar(traduccio, 1, 'E');
                }
                //v ==> E
                else if (comprova(traduccio, "v") and programa[i + 1] != '=') {
                    modificar = true;
                    canviar(traduccio, 1, 'E');
                }
                //E*E ==> E
                else if (comprova(traduccio, "E*E")) {
                    modificar = true;
                    canviar(traduccio, 3, 'E');
                }
                //E+E ==> E
                else if (comprova(traduccio, "E+E") and programa[i + 1] != '*') {
                    modificar = true;
                    canviar(traduccio, 3, 'E');
                }
                //E<E ==> E
                else if (comprova(traduccio, "E<E") and programa[i + 1] != '+'
                         and programa[i + 1] != '*') {
                    modificar = true;
                    canviar(traduccio, 3, 'E');
                }
                //v=E; ==> I
                else if (comprova(traduccio, "v=E;")) {
                    modificar = true;
                    canviar(traduccio, 4, 'I');
                }
                //(E) ==> E
                else if (comprova(traduccio, "(E)")
                        and not comprova(traduccio, "i(E)")
                        and not comprova(traduccio, "w(E)")) {
                    modificar = true;
                    canviar(traduccio, 3, 'E');
                }
                //i(E)I ==> I
                else if (comprova(traduccio, "i(E)I") and programa[i + 1] != 'e') {
                    modificar = true;
                    canviar(traduccio, 5, 'I');
                }
                //i(E)IeI ==> I
                else if (comprova(traduccio, "i(E)IeI")) {
                modificar = true;
                canviar(traduccio, 7, 'I');
                }
                //w(E)I ==> I
                else if (comprova(traduccio, "w(E)I")) {
                    modificar = true;
                    canviar(traduccio, 5, 'I');
                }
                //LI ==> L
                else if (comprova(traduccio, "LI")) {
                    modificar = true;
                    canviar(traduccio, 2, 'L');
                }
                //I ==> L
                else if (comprova(traduccio, "I") and not comprova(traduccio, "LI")
                         and not comprova(traduccio, ")I")) {
                    modificar = true;
                    canviar(traduccio, 1, 'L');
                }
                //{L} -> I
                else if (comprova(traduccio, "{L}")) {
                    modificar = true;
                    canviar(traduccio, 3, 'I');
                }
            }


        }
       if (traduccio == "L") traduccio = "P";
       cout << traduccio << endl;
    }
}
