#include<iostream>
using namespace std;
int main(){
    int number;
    bool break_loop = false;
    int position = 0;
    while (not break_loop and cin >> number) {
        if (number % 2 == 0) {
            break_loop = true;
        }
        ++position;
    }
    cout << position << endl;
}
