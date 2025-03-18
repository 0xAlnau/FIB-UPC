#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

#include "BinTree.hh"

int getIdVar(string s)
{
 return atoi(s.substr(1).c_str());
}

int suma(const BinTree<int>& t) {
    int resultat = 0;
    if (t.empty()) {}
    else {
        resultat += t.value() + suma(t.left()) + suma(t.right());
    }
    return resultat;
}

int mida(const BinTree<int>& t) {
    int resultat = 0;
    if (t.empty()) {}
    else {
        resultat += 1;
        int mida_l = mida(t.left());
        int mida_r = mida(t.right());
        resultat += mida_l + mida_r;
    }
    return resultat;
}

int main()
{
 string s1, s2, s3, s4, s5, s6, s7;
 int numvars;
 cin >> s1 >> numvars >> s2;
 vector<BinTree<int>> variables(numvars);

 while (cin >> s1 >> s2) {
  if (s1[0] == 't') {
   int idvar = getIdVar(s1);
   if (s2 == "=BinTree(") {
    int value;
    cin >> value >> s3 >> s4 >> s5 >> s6 >> s7;
    int idvar1 = getIdVar(s4);
    int idvar2 = getIdVar(s6);

    variables[idvar] = BinTree<int> (value, variables[idvar1], variables[idvar2]);
   }

   else if (s2 == "=") {
    cin >> s3 >> s4;
    int idvar1 = getIdVar(s3);
    if (s4 == ".left();") {
     variables[idvar] = variables[idvar1].left();
    } else {
     variables[idvar] = variables[idvar1].right();
    }
   }
  }

  else if (s1 == "cout<<") {
   int idvar = getIdVar(s2);
   cin >> s3;
   variables[idvar].setOutputFormat(BinTree<int>::INLINEFORMAT);
   cout << variables[idvar] << endl;
  } else if (s1 == "cout<<size(") {
   int idvar = getIdVar(s2);
   cin >> s3;
   cout << mida(variables[idvar]) << endl;
  } else if (s1 == "cout<<sum(") {
   int idvar = getIdVar(s2);
   cin >> s3;
   cout << suma(variables[idvar]) << endl;
  }
 }
}
