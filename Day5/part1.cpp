#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  int m = 0;
  while (cin >> s) {
    int r = 0;
    for (char c : s) {
      if (c == 'B' || c == 'R') r = r*2+1;
      else if (c == 'L' || c == 'F') r *= 2;
    }
    if (r > m) m = r;
  }
  cout << m << endl;
}
