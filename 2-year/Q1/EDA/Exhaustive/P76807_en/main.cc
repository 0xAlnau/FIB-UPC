#include<iostream>
#include<vector>
using namespace std;

bool found = false;

int num_casella(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}

void solve_sudoku(vector<vector<char>>& sudoku, vector<vector<bool>>& fila, vector<vector<bool>>& columna, vector<vector<bool>>& casella, vector<pair<int,int>>& cela_buida, int index) {
    if (cela_buida.size() == index) {
        found = true;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (j == 8) cout << sudoku[i][j] << endl;
                else cout << sudoku[i][j] << " ";
            }
        }
    }
    else if (not found) {
        int x = cela_buida[index].first;
        int y = cela_buida[index].second;
        for (int u = 0; u < 9; ++u) {
            if (not fila[x][u] and not columna[y][u] and not casella[num_casella(x,y)][u]) {
                sudoku[x][y] = (u+1) + '0';
                fila[x][u] = true;
                columna[y][u] = true;
                casella[num_casella(x,y)][u] = true;

                solve_sudoku(sudoku, fila, columna, casella, cela_buida, index+1);

                casella[num_casella(x,y)][u] = false;
                fila[x][u] = false;
                columna[y][u] = false;
                sudoku[x][y] = '.';
            }
        }
    }
    else return;
}

int main() {
    int n_sudokus;
    cin >> n_sudokus;
    cout << n_sudokus << endl << endl;
    while (n_sudokus != 0) {
        found = false;
        vector<vector<char>> sudoku(9, vector<char>(9));
        vector<vector<bool>> fila(9, vector<bool>(9, false)); //fila[0][8] mira si en la fila 0 hi ha el 9
        vector<vector<bool>> columna(9, vector<bool>(9, false)); // columna[2][7] mira si en la columna 2 està el 8
        vector<vector<bool>> casella(9, vector<bool>(9, false)); //casella[5][8] mira si en la casella 0 està el 9
        vector<pair<int,int>> cela_buida;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cin >> sudoku[i][j];
                if (sudoku[i][j] != '.') {
                    fila[i][(sudoku[i][j] - '0') - 1] = true;
                    columna[j][(sudoku[i][j] - '0') - 1] = true;
                    casella[num_casella(i,j)][(sudoku[i][j] - '0') - 1] = true;
                }
                else cela_buida.push_back({i,j});
            }
        }
        solve_sudoku(sudoku, fila, columna, casella, cela_buida, 0); //começarem a resoldre el sudoku per la primera casella
        --n_sudokus;
        if (n_sudokus != 0) cout << endl;
    }
}
