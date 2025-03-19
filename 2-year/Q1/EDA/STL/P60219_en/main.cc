#include<iostream>
#include<string>
#include<set>
using namespace std;

struct comp {
    bool operator () (const string& l, const string& r) const {
        bool first_l = false;
        if (l.length() < r.length()) first_l = true;
        else if (l.length() > r.length()) first_l = false;
        else first_l = l < r;

        return first_l;
    }
};


int main(){
    set<string> has;
    set<string, comp> had;

    string word;
    bool end = false;
    int count = 1;

    while (not end and cin >> word) {
        if (word == "END") {
            cout << "GAME #" << count <<endl;
            cout << "HAS:" <<endl;
            auto it = has.begin();
            auto end = has.end();

            while (it != end) {
                cout << *it <<endl;
                ++it;
            }

            cout <<endl<< "HAD:" <<endl;
            auto it2 = had.begin();
            auto end2 = had.end();

            while (it2 != end2) {
                cout << *it2 <<endl;
                ++it2;
            }
            cout<<endl;
            has.clear();
            had.clear();
            ++count;
        }

        else if (word == "QUIT") {
            end = true;
            cout << "GAME #" << count <<endl;
            cout << "HAS:" <<endl;
            auto it = has.begin();
            auto end = has.end();

            while (it != end) {
                cout << *it <<endl;
                ++it;
            }

            cout <<endl<< "HAD:" <<endl;
            auto it2 = had.begin();
            auto end2 = had.end();

            while (it2 != end2) {
                cout << *it2 <<endl;
                ++it2;
            }

        }

        else {
            if (has.count(word)) {
                has.erase(word);
                had.insert(word);
            }

            else {
                if (had.count(word)) {
                    had.erase(word);
                    has.insert(word);
                }

                else has.insert(word);
            }
        }
    }
}
