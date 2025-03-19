#include<iostream>
#include<set>
using namespace std;

int main() {
    set<long> bag;
    set<long> untouched;
    int capacity;
    long sum = 0;
    int actual_capacity = 0;
    cin >> capacity;

    string action;
    long value;
    while (cin >> action >> value) {
        if (action == "leave") {
            if (bag.empty()) {
                sum += value;
                bag.insert(value);
                ++actual_capacity;
            }
            else {
                if (actual_capacity < capacity) {
                    sum += value;
                    bag.insert(value);
                    ++actual_capacity;
                }
                else {
                    auto it = bag.begin();
                    if (*it < value) {
                        untouched.insert(*it);

                        sum -= *it;
                        bag.erase(it);
                        bag.insert(value);
                        sum += value;
                    }
                    else untouched.insert(value);
                }
            }
        }
        else { //action == "take"
            if (bag.count(value) == 1) {
                bag.erase(value);
                sum -= value;
                --actual_capacity;
            }

            if (untouched.count(value) == 1) untouched.erase(value);

            if (not untouched.empty()) {
                if (actual_capacity < capacity) {
                    auto end = untouched.end();
                    --end;
                    sum += *end;
                    ++actual_capacity;
                    bag.insert(*end);
                    untouched.erase(end);
                }
                else if (not bag.empty() and actual_capacity == capacity) {
                    auto it = bag.begin();
                    auto end = untouched.end();
                    --end;
                    if (*it < *end) {
                        untouched.insert(*it);

                        sum -= *it;
                        bag.erase(it);
                        bag.insert(*end);
                        sum += *end;
                    }
                }
            }
        }
        cout << sum << endl;
    }
}
