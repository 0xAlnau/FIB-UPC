#include<iostream>
#include<vector>
using namespace std;
struct goals {
    int x, y;
};
struct team {
    int plasa, punts, marcats, encaixats;
};

typedef vector<vector<goals>> Matrix;

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
    int mida;
    cin >> mida;
    Matrix partidos(mida, vector<goals> (mida));
    vector<team> equip(mida);
    for (int k = 0; k < mida; ++k) {
        equip[k].plasa = k + 1;
    }
    for (int i = 0; i < mida; ++i) {
        for (int j = 0; j < mida; ++j) {
            cin >> partidos[i][j].x;
            cin >> partidos[i][j].y;
            if (i == j) {}
            else {
                equip[i].marcats += partidos[i][j].x;
                equip[i].encaixats += partidos[i][j].y;
                equip[j].marcats += partidos[i][j].y;
                equip[j].encaixats += partidos[i][j].x;
                if (partidos[i][j].x > partidos[i][j].y) {
                    equip[i].punts += 3;
                }
                else if (partidos[i][j].x < partidos[i][j].y) {
                    equip[j].punts += 3;
                }
                else {
                    equip[i].punts += 1;
                    equip[j].punts += 1;
                }
            }
        }
    }
    ordenar(equip, mida);
    for (int m = 0; m < mida; ++m) {
        cout << equip[m].plasa << " " << equip[m].punts << " " << equip[m].marcats << " " << equip[m].encaixats <<endl;
    }
}
