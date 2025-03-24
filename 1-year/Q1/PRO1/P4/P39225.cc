#include<iostream>
using namespace std;
int main(){
    int i, index = 1;
    cin >> i;
    bool break_loop = false;
    int numbers;

    while (not break_loop and numbers != -1) {
        cin >> numbers;
        if (index == i) break_loop = true;
        ++index;
    }

    cout << "At the position " << i << " there is a(n) "<< numbers << "." <<endl;
}



