#include<iostream>
#include<vector>
using namespace std;

int index(int fixed_point, const vector<int>& v, int esq, int dret) {
    if (esq > dret) return -1;
    else {
        int m = (esq+dret) / 2;
        if (v[m] + fixed_point == m and (m == esq or v[m-1] + fixed_point != m-1)) return m;
        else if (v[m] + fixed_point < m) return index(fixed_point, v, m+1, dret);
        else return index(fixed_point, v, esq, m-1);
    }
}

int main(){
    int n, cas = 1;
    while (cin >> n) {
        vector<int> v(n+1, 0);
        for (int i = 1; i <= n; ++i) cin >> v[i];

        int fixed_points, fixed_point;
        cin >> fixed_points;
        cout << "Sequence #" << cas << endl;

        while (fixed_points != 0) {
            cin >> fixed_point;
            int position = index(fixed_point, v, 1, v.size()-1);

            if (position == -1) cout << "no fixed point for " << fixed_point << endl;
            else cout << "fixed point for " << fixed_point << ": " << position <<endl;
            --fixed_points;
        }
        cout << endl;
        ++cas;
    }
}
