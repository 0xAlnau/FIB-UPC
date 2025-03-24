//programa que te dira si el ambiente esta caliente, bien o frio, tambien indica si el agua herviria o no
//input: numero entero en celsius
//output: indicar como esta el ambiente, y si necesario, indicar si agua se helaria o herviria
#include<iostream>
using namespace std;
int main () {
    int t;
    cin >> t;
      if (t <= 0 and t < 10) {
        cout << "it's cold" <<endl;
        cout << "water would freeze" << endl;
        else { cout << "it's cold" << endl;}
                           }



      else if (t >= 100 or t >30) {
        cout << "it's hot" <<endl;
        cout << "water would boil" << endl;
        else { cout << "it's hot" << endl;}
                           }

      else if (t <= 30 and t >= 100) {
         cout <<  "it's ok" << endl;
      }



    }
