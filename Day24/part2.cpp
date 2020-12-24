#include <iostream>
#include <string>
#include <set>
using namespace std;

const pair<int,int> offsets[6] = {{1,0},{1,-1},{0,-1},{-1,0},{-1,1},{0,1}};

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

  for (auto p : flipped) cout << p.first << ',' << p.second << ' ';
  cout << endl;

  for (int i = 0; i < 100; i++) {
    cout << flipped.size() << endl;
    set<pair<int,int>> new_flipped;
    set<pair<int,int>> visited;
    for (auto p : flipped) {
      int y = p.first, x = p.second;
      int ctr = 0;
      for (auto o : offsets) {
        int dy = o.first, dx = o.second;
        if (flipped.find({y+dy,x+dx}) != flipped.end()) ctr++;
      }
      if (ctr == 1 || ctr == 2) new_flipped.insert({y,x});

      for (auto o : offsets) {
        int dy = o.first, dx = o.second;
        if (flipped.find({y+dy,x+dx}) != flipped.end()) continue;
        if (visited.find({y+dy,x+dx}) != visited.end()) continue;
        visited.insert({y+dy,x+dx});
        int ctr = 0;
        for (auto o2 : offsets) {
          int dy2 = o2.first, dx2 = o2.second;
          if (flipped.find({y+dy+dy2,x+dx+dx2}) != flipped.end()) ctr++;
        }
        if (ctr == 2) new_flipped.insert({y+dy,x+dx});
      }
    }
    flipped = new_flipped;
  }

  cout << flipped.size() << endl;
}
