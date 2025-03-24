#include<iostream>
#include<vector>
#include<string>
using namespace std;
typedef vector<vector<char>> Matrix;

vector<string> read_vector(int size){
    vector<string> V(size);
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}
//esta funcion creara un vector contador, donde
//cada espacio representa una letra,
//y si en un vector de strings hay una
//letra se dice que existe añadiendo 1
//al vector contador
//Pre: un vector de strings y su tamaño
//Post: vector contador
vector<int> abecedario(const vector<string>& V, int size){
    vector<int>contador_letras(27,0);
    for (int i = 0; i < size; ++i) {
        int size2 = V[i].length();
        for (int j = 0; j < size2; ++j) {
            ++contador_letras[V[i][j] - 'a'];
        }
    }
    return contador_letras;
}

Matrix read_matrix(int nrows, int ncolumns){
    Matrix M(nrows, vector<char>(ncolumns));
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncolumns; ++j) {
            cin >> M[i][j];
        }
    }
    return M;
}
//esta accion imprimira una matriz dada, pero cambiando
//de minuscula a mayuscula si una letra se encuentra en
//una palabra anterior dada
//Pre: una matriz de letras, dos enteros para su tamaño,
// y un vector contador
//Post: la matriz cambiada
void sopa_done(Matrix& M, int m, int n, vector<int> V){
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            bool found = false;
            for (int k = 0; not found and k < 27; ++k) {
                if (V[M[i][j] - 'a'] != 0) {
                    M[i][j] = M[i][j] - ('a' - 'A');
                    found = true;
                }
            }
            cout << M[i][j] << " ";
        }
        cout<<endl;
    }
}
//este programa con la ayuda de las otras
//funciones remarcara las letras que hayan en
//una serie de palabras dadas
int main(){
    int x,m,n;
    while (cin >> x >> m >> n) {
        vector<string> names = read_vector(x);
        vector<int> letras = abecedario(names, x);
        Matrix sopa = read_matrix(m,n);
        cout<<endl;
        sopa_done(sopa, m, n, letras);
    }

}




