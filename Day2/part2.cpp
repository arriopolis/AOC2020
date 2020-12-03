#include <iostream>
#include <string>
using namespace std;

int main() {
  int l,u;
  char c,d;
  string s;
  int ctr = 0;
  while (cin >> l >> c >> u >> c >> d >> s) {
    if (s[l-1] == c && s[u-1] == c) continue;
    if (s[l-1] == c || s[u-1] == c) ctr++;
  }
  cout << ctr << endl;
}
