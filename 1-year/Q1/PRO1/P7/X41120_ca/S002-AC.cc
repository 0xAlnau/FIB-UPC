#include<iostream>
#include<vector>
using namespace std;
vector<int> read_in(int& size){
    cin >> size;
    vector<int> V(size);
    for (int i = 0; i < size; ++i) {
        cin >> V[i];
    }
    return V;
}
// PRE: |v|≥ 3
// POST: returns a vector containing the height of all the peaks in v (in the same order)
vector<int> obtain_peaks(const vector<int>& v, int size, int& contador){
    vector<int> peaks (0);
    for(int i = 1; i < size - 1; ++i) {
        if (v[i - 1] < v[i] and v[i] > v[i + 1]) {
            ++contador;
            peaks.push_back(v[i]);
        }
    }
    return peaks;
}

int main (){
    int size = 0, contador = 0;
    vector<int> mountain = read_in(size);
    vector<int> peaks = obtain_peaks(mountain, size, contador);
    cout << contador << ":";
    for (int i = 0; i < contador; ++i) {
        cout << " " << peaks[i];
    }
    cout<<endl;
    bool mayor = false;
    for (int j = 0; j < contador - 1; ++j) {
        if (peaks[contador - 1] > peaks[j]) {}
        else if (not mayor and peaks[contador - 1] < peaks[j]){
            cout <<peaks[j];
            mayor = true;
        }
        else if (mayor and peaks[contador - 1] < peaks[j]){
            cout <<" "<<peaks[j];
        }
    }
    if (not mayor) {cout << "-" <<endl;}
    else {cout <<endl;}
}
