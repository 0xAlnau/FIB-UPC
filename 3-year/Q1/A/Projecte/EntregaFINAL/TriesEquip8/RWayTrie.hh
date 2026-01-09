#include<iostream>
#include<vector>
#include<string>
#include<chrono>
#include"NodeRWay.hh"
using namespace std;

class RWayTrie {
private:

    uint size = 1; // tenim en compte l'arrel

    int d_max = 0;

    NodeRWay* arrel = new NodeRWay;

    NodeRWay* insertar(NodeRWay* n, string key, int valor, int d);

    NodeRWay* get(NodeRWay* n, string key, int d, int& nodes_vis, int& prof);

    void autocompletar_rec(NodeRWay* n, vector<string>& paraules, string paraula_construida, chrono::time_point<std::chrono::high_resolution_clock>& middle, int& nodes_apartir_prefix);

public:

    uint getSize(); //retorna el nombre de nodes total

    uint getSizeBnode(); //retorna la mida en bytes d'un node RWay

    int getProfunditat();

    void insertar(string key, int valor);

    bool conte(string key);

    NodeRWay* get(string key, int& nodes_vis, int& prof);

    vector<string> autocompletar(NodeRWay* n, string paraula, chrono::time_point<std::chrono::high_resolution_clock>& middle, int& nodes_apartir_prefix);

};
