#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  set<pair<int,int>> flipped;

  string s;
  while (getline(cin,s)) {
    int y = 0, x = 0;
    while (s.size() > 0) {
      char c = s[0];
      s = s.substr(1);
      if (c == 'w') x--;
      else if (c == 'e') x++;
      else {
        char d = s[0];
        s = s.substr(1);
        if (d == 'e' && c == 'n') y++;
        else if (d == 'w' && c == 's') y--;
        else if (d == 'w' && c == 'n') {x--; y++;}
        else if (d == 'e' && c == 's') {x++; y--;}
      }
    }
    if (flipped.find({y,x}) == flipped.end()) {
      flipped.insert({y,x});
    } else {
      flipped.erase({y,x});
    }
  }

  cout << flipped.size() << endl;
}
