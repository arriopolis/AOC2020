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

  int startx = 0;
  int starty = 0;
  int ctr = 0;
  while (starty < h) {
    if (grid[starty][startx]) ctr++;
    startx = (startx + 3) % w;
    starty++;
  }

  cout << ctr << endl;
}
