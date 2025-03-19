#include<iostream>
#include<queue>
using namespace std;

int main() {
    int number;
    while (cin >> number) {
        priority_queue<int> cua;
        cua.push(number);
        while (cin >> number) cua.push(number);
        cout << cua.size() << endl;
    }


}
