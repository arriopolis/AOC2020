#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
  string s;
  vector<vector<char>> tmp_grid;
  while (getline(cin,s)) {
    vector<char> grid_line;
    for (char c : s) {
      grid_line.push_back(c);
    }
    tmp_grid.push_back(grid_line);
  }

  int h = tmp_grid.size(), w = tmp_grid[0].size();
  char grid[h][w];
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      grid[y][x] = tmp_grid[y][x];
    }
  }

  bool changed = true;
  // int num_iter = 0;
  while (changed) {
    changed = false;
    char new_grid[h][w];
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (grid[y][x] == '.') {
          new_grid[y][x] = '.';
        } else {
          int ctr = 0;
          for (int dy = -1; dy < 2; dy++) {
            for (int dx = -1; dx < 2; dx++) {
              if (dy == 0 && dx == 0) continue;
              for (int m = 1; m < max(h,w); m++) {
                int newy = y+m*dy, newx = x+m*dx;
                if (newy < 0 || newy >= h) break;
                if (newx < 0 || newx >= w) break;
                if (grid[newy][newx] == 'L') break;
                if (grid[newy][newx] == '#') {
                  ctr++;
                  break;
                }
              }
            }
          }
          if (grid[y][x] == 'L' && ctr == 0) {
            new_grid[y][x] = '#';
            changed = true;
          } else if (grid[y][x] == '#' && ctr >= 5) {
            new_grid[y][x] = 'L';
            changed = true;
          } else {
            new_grid[y][x] = grid[y][x];
          }
        }
      }
    }

    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        grid[y][x] = new_grid[y][x];
        // cout << grid[y][x];
      }
      // cout << endl;
    }
    // cout << endl;

    // if (num_iter++ == 2) {
    //   break;
    // }
  }

  int ctr = 0;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (grid[y][x] == '#') {
        ctr++;
      }
    }
  }

  cout << ctr << endl;
}
