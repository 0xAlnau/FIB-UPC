#include<iostream>
#include<map>
using namespace std;

int main(){
    cout.setf(ios::fixed);
    cout.precision(4);

    map<int,int> numbers;
    double average = 0, count = 0;
    string operation;
    int number, minimum = 0, maximum = 0;

    while (cin >> operation) {
        if (operation == "number") {
            cin >> number;

            if (numbers.empty()) {
                maximum = number;
                minimum = number;
            }
            else {
                auto it = numbers.begin();
                if (number < it->first) minimum = number;
                else {
                    it = numbers.end();
                    --it;
                    if (number > it->first) maximum = number;
                }
            }

            ++numbers[number];
            ++count;
            average += number;

            cout << "minimum: " << minimum << ", maximum: " << maximum << ", average: " << average / count << endl;

        }

        else {
            auto it = numbers.begin();
            if (it == numbers.end()) cout << "no elements" << endl;
            else {
                if (it->second > 1) {
                    --numbers[it->first];
                    --count;
                    average -= it->first;
                    cout << "minimum: " << minimum << ", maximum: " << maximum << ", average: " << average / count << endl;
                }
                else {
                    --count;
                    average -= it->first;
                    numbers.erase(it);
                    if (numbers.empty()) cout << "no elements" << endl;
                    else {
                        it = numbers.begin();
                        minimum = it->first;
                        cout << "minimum: " << minimum << ", maximum: " << maximum << ", average: " << average / count << endl;
                    }
                }
            }
        }
    }
}
