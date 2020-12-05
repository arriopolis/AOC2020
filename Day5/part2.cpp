#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  string s;
  vector<int> ids;
  while (cin >> s) {
    int r = 0;
    for (char c : s) {
      if (c == 'B' || c == 'R') r = r*2+1;
      else if (c == 'L' || c == 'F') r *= 2;
    }
    ids.push_back(r);
  }

  sort(ids.begin(), ids.end());

  for (int i = 0; i < ids.size(); i++) {
    if (ids[i] != i+85) {
      cout << i+85 << endl;
      break;
    }
  }
}
