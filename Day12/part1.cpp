#include <iostream>
#include <string>
using namespace std;

const pair<int,int> dirs[4] = {{1,0},{0,1},{-1,0},{0,-1}};

int main() {
  string s;
  int dir = 0;
  int x = 0, y = 0;
  while (getline(cin,s)) {
    // cout << s << " : ";
    char c = s[0];
    if (c == 'E') x += stoi(s.substr(1));
    else if (c == 'N') y += stoi(s.substr(1));
    else if (c == 'W') x -= stoi(s.substr(1));
    else if (c == 'S') y -= stoi(s.substr(1));
    else if (c == 'L' || c == 'R') {
      int d = stoi(s.substr(1));
      if (d%90 != 0) {
        cout << "The number of degrees was not a multiple of 90." << endl;
        return 1;
      }
      d /= 90;
      if (c == 'L') dir = (dir+d)%4;
      if (c == 'R') dir = (dir+4-d)%4;
    }
    else if (c == 'F') {
      int dx = dirs[dir].first, dy = dirs[dir].second;
      int m = stoi(s.substr(1));
      x += m*dx, y += m*dy;
    }
    // cout << x << ',' << y << endl;
  }

  cout << abs(x) + abs(y) << endl;
}
