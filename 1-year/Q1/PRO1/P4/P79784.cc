#include<iostream>
#include<string>
using namespace std;
int main(){
    string sequence;
    int cordinates1 = 0, cordinates2 = 0;
    cin >> sequence;
    int size = sequence.length();
    char coordinate;
    for (int i = 0; i < size; ++i) {
        coordinate = sequence[i];
        if (coordinate == 'n') --cordinates2;
        else if (coordinate == 's') ++cordinates2;
        else if (coordinate == 'w') --cordinates1;
        else ++cordinates1;
    }
    cout << "(" << cordinates1 << ", " << cordinates2 << ")" <<endl;
}
