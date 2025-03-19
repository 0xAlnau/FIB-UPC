#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
void order_vec(vector<string>& v, int& size) {
    int left = v[0];
    int right = v[size-1];
    bool end = false;
    while (not end and left < right) {

    }

}
*/

int main(){
    vector<string> words;
    string word;
    cin >> word;
    int count = 0, enter;
    while (word != "END") {
        words.push_back(word);
        ++count;

        sort(words.begin(), words.end());

        //int size = words.size();
        //for (int i = 0; i < size; ++i) cout << words[i] << " ";
        //cout << endl;

        enter = (count + 1) / 2;
        cout << words[enter-1] << endl;
        cin >> word;
    }
}
