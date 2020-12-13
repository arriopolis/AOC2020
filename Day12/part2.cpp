#include <iostream>
#include <string>
using namespace std;

const pair<int,int> dirs[4] = {{1,0},{0,1},{-1,0},{0,-1}};

int main() {
  string s;
  int dir = 0;
  int x = 0, y = 0;
  int wx = 10, wy = 1;
  while (getline(cin,s)) {
    char c = s[0];
    if (c == 'E') wx += stoi(s.substr(1));
    else if (c == 'N') wy += stoi(s.substr(1));
    else if (c == 'W') wx -= stoi(s.substr(1));
    else if (c == 'S') wy -= stoi(s.substr(1));
    else if (c == 'L' || c == 'R') {
      int d = stoi(s.substr(1));
      if (d%90 != 0) {
        cout << "The degrees is not a multiple of 90." << endl;
        return 1;
      }
      d /= 90;
      if (c == 'R') d = (d*3)%4;
      for (int i = 0; i < d; i++) {
        int newwx = -wy, newwy = wx;
        wx = newwx, wy = newwy;
      }
    }
    else if (c == 'F') {
      int m = stoi(s.substr(1));
      x += m*wx, y += m*wy;
    }
  }

  cout << abs(x) + abs(y) << endl;
}
