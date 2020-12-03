#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
  int l,u;
  char c,d;
  string s;
  int ctr = 0;
  while (cin >> l >> c >> u >> c >> d >> s) {
    // cout << l << ',' << u << ',' << c << ',' << s << endl;
    map<char,int> chars;
    for (char c2 : s) chars[c2]++;
    if (l <= chars[c] && chars[c] <= u) ctr++;
  }
  cout << ctr << endl;
}
