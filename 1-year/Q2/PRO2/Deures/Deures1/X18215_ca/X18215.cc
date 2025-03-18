#include <iostream>
#include <string>
using namespace std;

/* Aquesta funcio s'encarrega de comprovar de que si
   la part final del string traduccio coincideix amb
   una de totes les regles predefinides
   //Pre: dos strings, un amb la traduccio actual del
   programa, i un altre amb la regla a comprovar
   //Post: true si compleix la regla, false d'altra banda
   */
bool comprova(const string& traduccio, string regla){
    int size_regla = regla.length();
    int size_traduccio = traduccio.length();
    if (size_regla > size_traduccio) return false;

    int i = size_traduccio - 1;
    int j = size_regla - 1;
    while (j >= 0) {
        if (regla[j] != traduccio[i]) return false;
        --i;
        --j;
    }
    return true;
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
        int size = programa.length();
        string traduccio;
        for (int i = 0; i < size; ++i) {
            traduccio.push_back(programa[i]);
            bool modificar = true;

            while (modificar) {
                modificar = false;

                //n ==> E
                if (comprova(traduccio, "n")) {
                    for (int j = 0; j < 1; ++j) traduccio.pop_back();
                    traduccio.push_back('E');
                    modificar = true;
                }
                //v ==> E
                else if (comprova(traduccio, "v") and programa[i+1] != '=') {
                    for (int k = 0; k < 1; ++k) traduccio.pop_back();
                    traduccio.push_back('E');
                    modificar = true;
                }
                //E*E ==> E
                else if (comprova(traduccio, "E*E")) {
                    for (int l = 0; l < 3; ++l) traduccio.pop_back();
                    traduccio.push_back('E');
                    modificar = true;
                }
                //E+E ==> E
                else if (comprova(traduccio, "E+E") and programa[i+1] != '*') {
                    for (int m = 0; m < 3; ++m) traduccio.pop_back();
                    traduccio.push_back('E');
                    modificar = true;
                }
                //E<E ==> E
                else if (comprova(traduccio, "E<E") and programa[i+1] != '+'
                         and programa[i+1] != '*') {
                    for (int n = 0; n < 3; ++n) traduccio.pop_back();
                    traduccio.push_back('E');
                    modificar = true;
                }
                //v=E; ==> I
                else if (comprova(traduccio, "v=E;")) {
                    for (int o = 0; o < 4; ++o) traduccio.pop_back();
                    traduccio.push_back('I');
                    modificar = true;
                }
                //(E) ==> E
                else if (comprova(traduccio, "(E)")
                        and not comprova(traduccio, "i(E)")
                        and not comprova(traduccio, "w(E)")) {
                    for (int p = 0; p < 3; ++p) traduccio.pop_back();
                    traduccio.push_back('E');
                    modificar = true;
                }
                //i(E)I ==> I
                else if (comprova(traduccio, "i(E)I") and programa[i+1] != 'e') {
                    modificar = true;
                    for (int q = 0; q < 5; ++q) traduccio.pop_back();
                    traduccio.push_back('I');
                    modificar = true;
                }
                //i(E)IeI ==> I
                else if (comprova(traduccio, "i(E)IeI")) {
                for (int r = 0; r < 7; ++r) traduccio.pop_back();
                    traduccio.push_back('I');
                    modificar = true;
                }
                //w(E)I ==> I
                else if (comprova(traduccio, "w(E)I")) {
                    for (int s = 0; s < 5; ++s) traduccio.pop_back();
                    traduccio.push_back('I');
                    modificar = true;
                }
                //LI ==> L
                else if (comprova(traduccio, "LI")) {
                    for (int t = 0; t < 2; ++t) traduccio.pop_back();
                    traduccio.push_back('L');
                    modificar = true;
                }
                //I ==> L
                else if (comprova(traduccio, "I") and not comprova(traduccio, "LI")
                         and not comprova(traduccio, ")I")) {
                    for (int u = 0; u < 1; ++u) traduccio.pop_back();
                    traduccio.push_back('L');
                    modificar = true;
                }
                //{L} -> I
                else if (comprova(traduccio, "{L}")) {
                    for (int v = 0; v < 3; ++v) traduccio.pop_back();
                    traduccio.push_back('I');
                    modificar = true;
                }
            }
        }
       if (traduccio == "L") traduccio = "P";
       cout << traduccio << endl;
    }
}
