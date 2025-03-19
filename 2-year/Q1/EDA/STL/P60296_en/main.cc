#include<iostream>
#include<map>
#include<set>
using namespace std;

struct comp {
    bool operator()(const pair<string,int>& l, const pair<string,int>& r) const
    {
        bool first = false;

        if(l.second > r.second) first = true;
        else if (l.second < r.second) first = false;
        else {
            first = l.first < r.first;
        }

        return first;
    }
};

int main(){
    map<string,pair<int,bool>> players;
    string operation, name = "", name2 = "";

    while (cin >> operation) {
        if (operation == "LOGIN") {
            cin >> name;

            if (players.count(name) == 0) {
                players[name].first = 1200;
                players[name].second = true;
            }

            else {
                if (players.count(name) == 1) {}//do nothing, has elo
                players[name].second = true;
            }

        }

        else if (operation == "LOGOUT") {
            cin >> name;

            if (players.count(name) == 0) {}

            else {
                players[name].second = false;
            }

        }

        else if (operation == "PLAY") {
            cin >> name >> name2;
            if (players.count(name) == 0 or players.count(name2) == 0) cout << "player(s) not connected" << endl;
            else if (not players[name].second or not players[name2].second) cout << "player(s) not connected" << endl;
            else {
                players[name].first += 10;

                if (players[name2].first >= 1210) players[name2].first -= 10;
            }
        }

        else { //GET_ELO
            cin >> name;
            if (players.count(name) == 0) {}
            else cout << name << " " << players[name].first << endl;
        }
    }

    set<pair<string,int>, comp> elo_ordered;
    auto it = players.begin();
    auto end = players.end();

    int count = 0;
    while (it != end) {
        pair<string,int> elo;
        elo.first = it->first;
        elo.second = it->second.first;
        elo_ordered.insert(elo);
        ++it;
        ++count;
    }

    cout << endl << "RANKING" <<endl;

    auto it2 = elo_ordered.begin();
    auto end2 = elo_ordered.end();
    while (it2 != end2) {
        cout << (*it2).first << " " << (*it2).second << endl;
        ++it2;
    }
}

