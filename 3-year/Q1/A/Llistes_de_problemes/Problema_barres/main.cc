#include<iostream>
#include<vector>
using namespace std;

void calcular_talls_prev(int n_act, const vector<int>& p, vector<int>& T, vector<vector<int>>& pos_talls, int& n)
{
    if (n_act == 1) T[1] = p[1];
    else {
        int no_tall = p[n_act]; //no tallem, agafem preu llargaria n
        int tall = 0;
        int tall_max = no_tall;
        for (int i = 1; i <= n_act - 1; ++i) { //podem fer n-1 talls
            tall = T[i] + T[n_act-i];
            if (tall > tall_max) {
                tall_max = tall;
                pos_talls[n_act] = pos_talls[n_act-i];
                pos_talls[n_act].push_back(n_act-i);
            }
        }
        T[n_act] = max(no_tall, tall_max);
        if (n_act == n) cout << "Guany màxim de: " <<  T[n] << endl;
    }
}

vector<int> calcular_talls(int n, const vector<int>& p)
{
    vector<vector<int>> pos_talls(n+1);
    vector<int> T(n+1, -1); //indica el millor cost per una barra de mida n

    for (int i = 1; i <= n; ++i) { //volem les mides fins a n-1
        calcular_talls_prev(i, p, T, pos_talls, n);
    }

    return pos_talls[n];
}

int main()
{
    int n;
    cout <<"Llargaria de la barra: ";
    cin >> n;

    vector<int> p(n+1);
    for (int i = 1; i <= n; ++i) {
        cout << "Preu llargaria " << i << ": ";
        cin >> p[i];
    }

    vector<int> talls = calcular_talls(n,p);
    cout << "Nombre de talls a fer: " << talls.size() << endl;
    for (int x : talls) cout << "Tall en la posició " << x << endl;

}
