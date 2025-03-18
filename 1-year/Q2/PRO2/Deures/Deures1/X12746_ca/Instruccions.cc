//Per fer aquest exercici calia triar un tipus de dada: s'ha triat map.

#include <iostream>
#include <string>
#include <map>

using namespace std;

//Funcio per aplicar comandes:
//  Pre: Rep l'string de comanda i el map per aplicar-la-hi, aixi com
//       els indexs minim i maxim d'aquest.
//  Post: Aplica la comanda, tot modificant el map i indexs, si cal.
void comanda(const string& c, map<int, int>& mp, int& indxMin, int& indxMax)
{
    //Afegeix un element al final del map.
    if (c == "v.push_back(") 
    {
        int val;
        cin >> val;
        string ending;
        cin >> ending;

        mp[indxMax] = val;
        ++indxMax;
    }
    //Afegeix un element a l'inici del map.
    else if (c == "v.push_front(") 
    {
        int val;
        cin >> val;
        string ending;
        cin >> ending;

        mp[indxMin] = val;
        --indxMin;
    }
    //Treu l'element a l'inici del map.
    else if (c == "v.pop_front();") 
    {
        ++indxMin;
        mp.erase(indxMin);
    }
    //Treu l'element al final del map.
    else if (c == "v.pop_back();") 
    {
        --indxMax;
        mp.erase(indxMax);
    }
    //Canvia la mida del map a la indicada, ja sigui major o menor.
    else if (c == "v.resize(") 
    {
        int newsize;
        cin >> newsize;
        string ending;
        cin >> ending;

        map<int, int>::iterator it = mp.lower_bound(indxMin + newsize + 1);
        while (it != mp.end()) {
            it = mp.erase(it);
        }

        indxMax = indxMin + newsize + 1;
    }
    //Imprimeix l'element del map indicat.
    else if (c == "cout<<v[") 
    {
        int index;
        cin >> index;
        string ending;
        cin >> ending;

        cout << mp[indxMin + index + 1] << endl;
    }
    //Imprimeix tot el map.
    else if (c == "cout<<v;") 
    {
        cout << mp[indxMin + 1];
        for (int i = indxMin + 2; i < indxMax; ++i) {
            cout << ',' << mp[i];
        }
        cout << endl;
    }
    //Canvia l'element del mapa corresponent.
    else if (c == "v[") 
    {
        int index;
        cin >> index;
        string mid;
        cin >> mid;
        int val;
        cin >> val;
        string ending;
        cin >> ending;

        mp[indxMin + index + 1] = val;
    }
    //Comentari (No fa res, imprimeix la comanda)
    else if (c == "//") 
    {
        string comment;
        getline(cin, comment);
        cout << "//" << comment << endl;
    }
    //Instruccio no valida
    else 
    {
        cout << "Wrong command '" << c << "'" << endl;
        string discard;
        getline(cin, discard);
    }
}

//Programa principal:
//  Va llegint les comandes d'entrada i les executa.
int main()
{
    map<int, int> mp;
    int indxMin = -1;
    int indxMax = 0;

    string command;
    while (cin >> command) {
        comanda(command, mp, indxMin, indxMax);
    }
}