#include <iostream>
#include <vector>
using namespace std;


void cross(int n, char c) {
  vector<char> col(n/2, ' ');
  vector<char> mig(n, c);
  col.push_back(c);

  for (int i = 0; i < n; ++i) {
    if (i == n/2) {
      for (int j = 0; j < n; ++j) cout << mig[j];
    }
    else {
      for (int j = 0; j < col.size(); ++j) cout << col[j];
    }
    cout << endl;
  }
}


int main() {
  int n;
  char c;
  while (cin >> n >> c) cross(n, c);
  return 0;
}
