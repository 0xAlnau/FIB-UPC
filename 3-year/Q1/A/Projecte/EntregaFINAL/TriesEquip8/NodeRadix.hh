#ifndef NODERADIX_H
#define NODERADIX_H

#include <map>
#include <string>
#include <vector>
using namespace std;

class NodeRadix {
public:
    vector<int> valor;
    string label;
    map<unsigned char, NodeRadix*> child = {};
    bool es_paraula = false;
};

#endif