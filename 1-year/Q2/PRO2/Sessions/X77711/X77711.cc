#include<iostream>
#include<vector>
using namespace std;
struct team {
    int plasa, punts, marcats, encaixats;
};

void ordenar(vector<team>& v, int size){
    for (int i = 0; i < size; ++i) {
        int recorr = 0;
        while (recorr != size) {
            if (recorr == i) {}
            else if (v[i].punts > v[recorr].punts) {
                team aux = v[i];
                v[i] = v[recorr];
                v[recorr] = aux;
            }
            else if (v[i].punts == v[recorr].punts) {
                if (v[i].marcats - v[i].encaixats > v[recorr].marcats - v[recorr].encaixats) {
                    team aux = v[i];
                    v[i] = v[recorr];
                    v[recorr] = aux;
                }
                else if (v[i].marcats - v[i].encaixats == v[recorr].marcats - v[recorr].encaixats) {
                    if (v[i].plasa < v[recorr].plasa) {
                    team aux = v[i];
                    v[i] = v[recorr];
                    v[recorr] = aux;
                    }
                }
            }
            ++recorr;
        }
    }
}

int main(){
    int mida, jornades;
    cin >> mida >> jornades;
    vector<team> equip(mida);
    for (int k = 0; k < mida; ++k) {
        equip[k].plasa = k + 1;
    }
    int partidos2 = mida / 2;
    int equip1, equip2, marca1, marca2;
    for (int i = 0; i < jornades; ++i) {
        for (int j = 0; j < partidos2; ++j) {
            cin >> equip1 >> equip2 >> marca1 >> marca2;
            equip[equip1 -1].marcats += marca1;
            equip[equip1 -1].encaixats += marca2;
            equip[equip2 -1].marcats += marca2;
            equip[equip2 -1].encaixats += marca1;
            if (marca1 > marca2) {
                equip[equip1 -1].punts += 3;
            }
            else if (marca1 < marca2) {
                equip[equip2 -1].punts += 3;
            }
            else {
                equip[equip1 -1].punts += 1;
                equip[equip2 -1].punts += 1;
            }
        }
    }
    ordenar(equip, mida);
    for (int m = 0; m < mida; ++m) {
        cout << equip[m].plasa << " " << equip[m].punts << " " << equip[m].marcats << " " << equip[m].encaixats <<endl;
    }
}
