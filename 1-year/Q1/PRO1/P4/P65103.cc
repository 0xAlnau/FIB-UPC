#include<iostream>
using namespace std;
int main(){
    int index = 1;
    int i;
    cin >> i;

    int number;
    bool found = false;
    while (not found and cin >> number) {
        if (index == i) found = true;
        ++index;
    }

    if (found) cout << "At the position " << i << " there is a(n) " << number << "." <<endl;
    else cout << "Incorrect position." <<endl;
}
