#include<iostream>
#include<unordered_map>
using namespace std;

int main(){
    int x, y, n;
    bool stop = false;
    unordered_map<int,int> cycle;

    while (cin >> x >> y >> n) {
        while (not stop and n <= 100000000) {
            if (n % 2 == 0) {
                if (cycle.count(n)) { //returns 1, si que hi és
                    stop = true;
                    auto it = cycle.find(n);
                    ++it;
                    cycle.erase(it, cycle.end());
                }
                else ++cycle[n];

                n = n/2 + x;
            }

            else {
                if (cycle.count(n)) { //returns 1, si que hi és
                    stop = true;
                    auto it = cycle.find(n);
                    ++it;
                    cycle.erase(it, cycle.end());
                }
                else ++cycle[n];

                n = 3*n + y;

            }
        }
        if (n > 100000000) cout << n << endl;
        else cout << cycle.size() << endl;
        cycle.clear();
        stop = false;
    }
}
