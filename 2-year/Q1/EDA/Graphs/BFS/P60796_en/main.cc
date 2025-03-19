//BFS, calcular distàncies!
//     -> totes les arestes han de tenir longitud almenys 1

//BFS:
//1-Volem saber la distàncies a tots els nodes, ho podem guardar a un vector!
//2-Amb una queue, poso el inicial (A), i miro els veins (B i C, en aquest ordre), i apunto
//  a quina distància estan i els afegeix-ho a la queue (per veure-ho al bucle for!!!)
//3- compares si pots arribar més ràpid del que podies abans (agafes distància d'on estàs i sumes al costat i  //   compares)
//4- quan canviem de infinit a finit, ja NO tornarà a canviar, llavors si ja tens la distància fins on vols,   //   pares!!!
//5- visitem en ordre de distància, quan trobes el que vols, es la trobada més petita que trobaràs mai!!!

#include<iostream>
#include<vector>
#include<limits>
#include<queue>
using namespace std;

const int INF = numeric_limits<int>::max();
typedef vector<vector<char>> Matrix;

//                              dre      esq     avall   amunt
vector<pair<int,int>> dirs = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool existeix_vei(Matrix& M, int f_vei, int c_vei) {
    int files = M.size();
    int columnes = M[0].size();

    return (f_vei >= 0 and f_vei < files and c_vei >= 0 and c_vei < columnes and M[f_vei][c_vei] != 'X');
}

int funcio_bfs(Matrix& M, int f, int c) {
    int resultat = -1;
    int n = M.size();
    int m = M[0].size();
    vector<vector<int>> distancies(n, vector<int>(m, INF));

    distancies[f][c] = 0;
    queue<pair<int,int>> Q;
    Q.push({f, c});

    while (resultat == -1 and not Q.empty()) {
        pair<int,int> u = Q.front();
        Q.pop();

        for (int i = 0; resultat == -1 and i < 4; ++i) {
            int f_v = u.first + dirs[i].first;
            int c_v = u.second + dirs[i].second;

            if (existeix_vei(M, f_v, c_v) and distancies[f_v][c_v] == INF) {
                Q.push({f_v, c_v});
                distancies[f_v][c_v] = distancies[u.first][u.second] + 1;
                if (M[f_v][c_v] == 't') resultat = distancies[f_v][c_v];
            }
        }
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

    int d = funcio_bfs(M, f-1, c-1);
    if (d == -1) cout << "no treasure can be reached" << endl;
    else cout << "minimum distance: " << d << endl;
}
