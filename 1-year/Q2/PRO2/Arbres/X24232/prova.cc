#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

void hasdot (string& s, bool& found, string& extension) {
    int size = s.length() -1;
    for (int i = size; not found and i != 0; --i) {
        if (s[i] == '.') found = true;
        else extension += s[i];
    }
    if (found) {
        reverse(extension.begin(), extension.end());
    }
}

int main(){
    bool dot = false;
    string extension = "";
    string prova;
    cin >> prova;
    hasdot(prova, dot, extension);
    cout << extension << endl;
    cout << dot << endl;
}
