#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string s;
  vector<string> ss;
  while (cin >> s) {
    ss.push_back(s);
  }

  int h = ss.size();
  int w = ss[0].size();
  bool grid[h][w];
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      grid[y][x] = (ss[y][x] == '#');
    }
  }

  // for (int y = 0; y < h; y++) {
  //   for (int x = 0; x < w; x++) {
  //     if (grid[y][x]) cout << '#';
  //     else cout << '.';
  //   }
  //   cout << endl;
  // }

  vector<pair<int,int>> slopes = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
  int f = 1;
  for (auto p : slopes) {
    int startx = 0;
    int starty = 0;
    int dx = p.first;
    int dy = p.second;
    // cout << dy << ',' << dx << endl;
    int ctr = 0;
    while (starty < h) {
      if (grid[starty][startx]) ctr++;
      startx = (startx + dx) % w;
      starty += dy;
    }
    // cout << ctr << endl;
    f *= ctr;
  }

  cout << f << endl;
}
