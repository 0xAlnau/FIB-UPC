//DFS(puc arribar?) o BFS(distancies) per solucionar-ho!
//Funció recursiva sobre els DFS, hem de posar marques, per no fer bucles infinits! (X)
//·Node = casella
//·Aresta = si

//DFS:
//1-Miro si està marcada
//2-Miro si és el que busquem
//3-Si no ho és, mirem els veins recursivament amb vector direccions (cal comprovar que són bons veïns)
#include<iostream>
#include<vector>
using namespace std;
typedef vector<vector<char>> Matrix;
//                              dre      esq     avall   amunt
vector<pair<int,int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}};


bool existeix_vei(Matrix& M, int& f_vei, int& c_vei) {
    int files = M.size();
    int columnes = M[0].size();

    return (f_vei >= 0 and f_vei < files and c_vei >= 0 and c_vei < columnes and M[f_vei][c_vei] != 'X');
}

bool funcio_dsf(Matrix& M, int f, int c) {
    bool resultat = false;

    if (M[f][c] == 't') resultat = true;
    else M[f][c] = 'X';
    for (int i = 0; not resultat and i < 4; ++i) { //iterem sobre dirs
        int f_vei = f + dirs[i].first;
        int c_vei = c + dirs[i].second;

        if (existeix_vei(M, f_vei, c_vei) and funcio_dsf(M, f_vei, c_vei)) resultat = true;
    }

    return resultat;
}

int main() {
    int files, columnes;
    cin >> files >> columnes;

    Matrix M(files, vector<char>(columnes));
    for (int i = 0; i < files; ++i) {
        for(int j = 0; j < columnes; ++j) {
            cin >> M[i][j];
        }
    }

    int f, c;
    cin >> f >> c;

    if (funcio_dsf(M, f-1, c-1)) cout << "yes" << endl;
    else cout << "no" << endl;
}
