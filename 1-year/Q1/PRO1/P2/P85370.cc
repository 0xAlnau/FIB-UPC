#include<iostream>
#include<cmath>
using namespace std;

int main(){
    double euros, impost, years;
    string type;
    cout.setf(ios::fixed);
    cout.precision(4);
    cin >> euros >> impost >> years >> type;
    impost = impost / 100;
    double capital = 0;

    if (type == "simple") {
        capital = euros + (euros * impost * years);
    }

    else {
        capital = euros * (pow(1 + impost, years));
    }

    cout << capital << endl;
}
