 #include <vector>
 using namespace std;

 struct parint {int prim, seg;};

 parint max_min1(const vector<int>& v)
 /* Pre: v.size()>0 */
 /* Post: el primer componente del resultado es el valor maximo de v;
    el segundo componente del resultado es el valor minimo de v */
 {
    parint a;
    int tamany = v.size();
    int min = v[0];
    int max = v[0];
    for (int i = 1; i < tamany;++i){
        if (v[i] < min) min = v[i];
        else if(v[i] > max) max = v[i];
    }
    a.prim = max;
    a.seg = min;
    return a;
}

 pair<int,int> max_min2(const vector<int>& v)
 /* Pre: v.size()>0 */
 /* Post: el primer componente del resultado es el valor maximo de v;
 el segundo componente del resultado es el valor minimo de v */
 {
     pair<int,int> a;
    int tamany = v.size();
    int y = v[0];
    int x = v[0];
    for (int i = 1; i < tamany;++i){
        if (v[i] < y) y = v[i];
        else if(v[i] > x) x = v[i];
    }
    a.first = x;
    a.second = y;
    return a;
}

 void max_min3(const vector<int>& v, int& x, int& y)
 /* Pre: v.size()>0 */
 /* Post: x es el valor maximo de v;  y es el valor minimo de v */
 {
    int tamany = v.size();
    y = v[0];
    x = v[0];
    for (int i = 1; i < tamany;++i){
        if (v[i] < y) y = v[i];
        else if(v[i] > x) x = v[i];
    }
}



