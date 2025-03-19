#include<iostream>
#include<map>
using namespace std;

//struct meva_comp {
//bool operator() (const string& lhs, const string& rhs) const {
//
//   }
//};

int main() {
    map<string, int> jugadors;
    string operation, name;
    int quantity;

    while (cin >> name) {
        cin >> operation;
        if (operation == "enters") {
            auto it = jugadors.find(name);
            if (it != jugadors.end()) cout << name << " is already in the casino" << endl;
            else jugadors[name] = 0;
        }

        else if (operation == "leaves") {
            auto it = jugadors.find(name);
            if (it == jugadors.end()) cout << name << " is not in the casino" << endl;
            else {
                cout << name << " has won " << jugadors[name] << endl;
                jugadors.erase(it);
            }

        }

        else { //someone wins
            cin >> quantity;
            auto it = jugadors.find(name);
            if (it == jugadors.end()) cout << name << " is not in the casino" << endl;
            else {
                jugadors[name] += quantity;
            }

        }
    }

    cout << "----------" << endl;
    if (jugadors.empty()) {}
    else {
        for (auto it : jugadors) cout << it.first << " is winning " << it.second <<endl;
    }
}
