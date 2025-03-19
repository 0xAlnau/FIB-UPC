#include<iostream>
#include<map>
using namespace std;

int main() {
    map<int,int> numbers;
    string op;
    int n;

    while (cin >> op) {
        if (op == "S") {
            cin >> n;
            ++numbers[n];
        }

        else if (op == "A") {
            if (numbers.empty()) cout << "error!" << endl;
            else {
                auto it = numbers.end();
                --it;
                cout << it->first << endl;
            }
        }

        else if (op == "R") {
            if (numbers.empty()) cout << "error!" << endl;
            else {
                auto it = numbers.end();
                --it;
                if (it->second == 1) numbers.erase(it);

                else --(it->second);
            }
        }

        else if (op == "I") {
            cin >> n;
            if (numbers.empty()) cout << "error!" << endl;
            else {
                auto it = numbers.end();
                --it;

                if (it->second == 1) {
                    ++numbers[(it->first) + n];
                    numbers.erase(it);
                }

                else {
                    ++numbers[(it->first) + n];
                    --numbers[it->first];
                }
            }
        }

        else { //D
            cin >> n;
            if (numbers.empty()) cout << "error!" << endl;
            else {
                auto it = numbers.end();
                --it;

                if (it->second == 1) {
                    ++numbers[(it->first) - n];
                    numbers.erase(it);
                }

                else {
                    ++numbers[(it->first) - n];
                    --numbers[it->first];
                }
            }
        }
    }
}
