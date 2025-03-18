#include <iostream>
#include <map>
#include <string>
using namespace std;

/* Aquest programa s'encarrega de simular una estructura
   de dades similar a un vector, on podem realitzar totes
   les seves funcions, i també podem fer pop_front() i pop_back()
   Input: un string, que indica quina instruccio ha de realitzar,
          i si cal un natural per indexos, o un enter per guardar
          dins d'el vector
   Output: si cal, una linia indicant el contingut del vector o
           nomes un element del vector
*/
int main(){
  string command;
  map<int,int> vector;
  int index_max = 0;
  int index_min = -1;
  while (cin >> command) {

    if (command == "v.push_back(") {
      int val;
      cin >> val;
      string ending;
      cin >> ending; // Això consumeix el ");"
      vector[index_max] = val;
      ++index_max;
      }

    else if (command == "v.push_front(") {
      int val;
      cin >> val;
      string ending;
      cin >> ending; // Això consumeix el ");"
      vector[index_min] = val;
        --index_min;
    }

    else if (command == "v.pop_front();") {
      ++index_min;
      vector.erase(index_min);
    }

    else if (command == "v.pop_back();") {
      --index_max;
      vector.erase(index_max);
    }

    else if (command == "v.resize(") {
      int newsize;
      cin >> newsize;
      string ending;
      cin >> ending; // Això consumeix el ");"
      map<int, int>::iterator it = vector.lower_bound(index_min + newsize + 1);
      while (it != vector.end()) it = vector.erase(it);
      index_max = index_min + newsize + 1;
    }

    else if (command == "cout<<v[") {
      int index;
      cin >> index;
      string ending;
      cin >> ending; // Això consumeix el "];"
      index = index_min + index + 1;
      cout << vector[index] << endl;
    }

    else if (command == "cout<<v;") {
      cout << vector[index_min + 1];
      int valor = index_min + 2;
      for (int i = valor; i < index_max; ++i) cout << ',' << vector[i];
      cout << endl;
    }
    else if (command == "v[") {
      int index;
      cin >> index;
      string mid;
      cin >> mid; // Això consumeix el "]="
      int val;
      cin >> val;
      string ending;
      cin >> ending; // Això consumeix el ";"
      index = index_min + index + 1;
      vector[index] = val;
    }
    else if (command == "//") {
      string comment;
      getline(cin, comment);
      cout << "//" << comment << endl;
    }
    else {
      cout << "Wrong command '" << command << "'" << endl;
      string discard;
      getline(cin, discard);
    }
  }
}

