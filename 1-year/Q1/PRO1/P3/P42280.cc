#include<iostream>
using namespace std;

int main(){
    int rows, columns;
    string coins;
    cin >> rows >> columns;
    int sum = 0;
    for (int i = 0; i < rows; ++i) {
        cin >> coins;
        for (int j = 0; j < columns; ++j) {
            sum += int(coins[j]) - '0';
        }
    }
    cout << sum << endl;
}

