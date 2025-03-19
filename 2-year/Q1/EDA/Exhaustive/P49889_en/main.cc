#include<iostream>
#include<vector>
using namespace std;

void escriure_paraules(const vector<char>& consonants, const vector<char>& vowels, vector<bool>& usat_c, vector<bool>& usat_v, vector<int>& resultat, bool consonant) {
    int n = consonants.size();
    if (2*n == resultat.size()) {
        for(int indx = 0; indx < 2*n; ++indx) {
            if (indx == 0 or indx % 2 == 0) cout << consonants[resultat[indx]];
            else cout << vowels[resultat[indx]];
        }
        cout << endl;
    }

    else {
        for (int i = 0; i < n; ++i) {
            if (consonant) {
                if (not usat_c[i]) {
                    usat_c[i] = true;
                    resultat.push_back(i);
                    escriure_paraules(consonants, vowels, usat_c, usat_v, resultat, false);

                    usat_c[i] = false;
                    resultat.pop_back();
                }
            }
            else {
                if (not usat_v[i]) {
                    usat_v[i] = true;
                    resultat.push_back(i);
                    escriure_paraules(consonants, vowels, usat_c, usat_v, resultat, true);

                    usat_v[i] = false;
                    resultat.pop_back();
                }
            }
        }
    }
}

void escriure_paraules(const vector<char>& consonants, const vector<char>& vowels) {
    int n = consonants.size();
    vector<bool> usat_c(n, false);//per les consosnants
    vector<bool> usat_v(n, false);//per les vocals
    vector<int> resultat; //guardarem indexos

    escriure_paraules(consonants, vowels, usat_c, usat_v, resultat, true);
}

int main() {
    int n;
    cin >> n;
    vector<char> consonants(n);
    vector<char> vowels(n);

    for (int i = 0; i < n; ++i) {
        cin >> consonants[i];
    }
    for (int j = 0; j < n; ++j) {
        cin >> vowels[j];
    }

    escriure_paraules(consonants, vowels);
}
