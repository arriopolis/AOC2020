#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

const pair<int,int> adjacent[4] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
const pair<int,int> monster[15] = {{1,0},{2,1},{2,4},{1,5},{1,6},{2,7},{2,10},{1,11},{1,12},{2,13},{2,16},{1,17},{1,18},{1,19},{0,18}};
const int mw = 20, mh = 3;

int main() {
  string s;
  vector<vector<bool>> tile;
  unordered_map<int,vector<vector<bool>>> tiles;
  int tile_id;
  while (getline(cin, s)) {
    if (s.size() == 0) {
      tiles[tile_id] = tile;
      tile.clear();
    } else if (s.substr(0,4) == "Tile") {
      tile_id = stoi(s.substr(5,s.size()-1));
    } else {
      vector<bool> row;
      for (char c : s) row.push_back(c == '#');
      tile.push_back(row);
    }
  }
  tiles[tile_id] = tile;
  int d = tile.size();

  // for (auto r : tiles[3011]) {
  //   for (auto c : r) {
  //     cout << (c ? '#' : '.');
  //   }
  //   cout << endl;
  // }
  // return 0;

  unordered_map<int,int[8][4]> borders;
  map<pair<int,int>,bool**> rotated_tiles;
  for (auto p : tiles) {
    tile = p.second;

    bool ** grid = new bool*[d];
    for (int y = 0; y < d; y++) {
      grid[y] = new bool[d];
      for (int x = 0; x < d; x++) {
        grid[y][x] = tile[y][x];
      }
    }

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 4; j++) {

        // Top, right, bottom, left
        pair<int,int> starts[4] = {{0,0},{0,d-1},{d-1,0},{0,0}};
        pair<int,int> steps[4] = {{0,1},{1,0},{0,1},{1,0}};

        // Parse to indices
        for (int k = 0; k < 4; k++) {
          auto start = starts[k];
          auto step = steps[k];
          int idx = 0;
          for (int l = 0; l < d; l++) {
            idx *= 2;
            if (grid[start.first + l*step.first][start.second + l*step.second]) idx++;
          }
          borders[p.first][4*i+j][k] = idx;
        }

        // Store the grid
        bool ** new_grid = new bool*[d];
        for (int y = 0; y < d; y++) {
          new_grid[y] = new bool[d];
          for (int x = 0; x < d; x++) {
            new_grid[y][x] = grid[y][x];
          }
        }
        rotated_tiles[{p.first,4*i+j}] = new_grid;

        // Rotate grid
        for (int k = 0; k < (d+1)/2; k++) {
          for (int l = 0; l < (d+1)/2; l++) {
            int tmp = grid[k][l];
            grid[k][l] = grid[l][d-1-k];
            grid[l][d-1-k] = grid[d-1-k][d-1-l];
            grid[d-1-k][d-1-l] = grid[d-1-l][k];
            grid[d-1-l][k] = tmp;
          }
        }
      }

      // Reflect grid
      for (int k = 0; k < d; k++) {
        for (int l = 0; l < d/2; l++) {
          int tmp = grid[k][l];
          grid[k][l] = grid[k][d-1-l];
          grid[k][d-1-l] = tmp;
        }
      }
    }

    for (int y = 0; y < d; y++) delete grid[y];
    delete grid;
  }

  // for (auto p : borders) {
  //   cout << p.first << endl;
  //   for (int i = 0; i < 8; i++) {
  //     cout << i << ": ";
  //     for (int j = 0; j < 4; j++) {
  //       cout << p.second[i][j] << ", ";
  //     }
  //     cout << endl;
  //   }
  // }

  auto neighbors = new set<pair<int,int>>*[4];
  for (int i = 0; i < 4; i++) neighbors[i] = new set<pair<int,int>>[1 << d];

  for (auto p : borders) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 4; j++) {
        neighbors[j][p.second[i][j]].insert({p.first,i});
      }
    }
  }

  // for (int i = 0; i < 4; i++) {
  //   cout << "Direction: " << i << endl;
  //   for (int j = 0; j < (1<<d); j++) {
  //     if (neighbors[i][j].size() == 0) continue;
  //     cout << j << ": ";
  //     for (auto p : neighbors[i][j]) {
  //       cout << '(' << p.first << ',' << p.second << ") ";
  //     }
  //     cout << endl;
  //   }
  // }

  map<pair<int,int>,pair<int,int>> grid;
  grid[{0,0}] = {tile_id,0};
  set<pair<int,int>> to_visit = {{-1,0},{0,1},{1,0},{0,-1}};
  unordered_set<int> placed = {tile_id};
  while (!to_visit.empty()) {
    auto p = *to_visit.begin();
    to_visit.erase(to_visit.begin());

    int y = p.first, x = p.second;
    bool first = true;
    set<pair<int,int>> poss;
    int i = 0;
    for (auto o : adjacent) {
      int dy = o.first, dx = o.second;
      if (grid.find({y+dy,x+dx}) != grid.end()) {
        tile_id = grid[{y+dy,x+dx}].first;
        int orientation = grid[{y+dy,x+dx}].second;
        int idx = borders[tile_id][orientation][(i+2)%4];

        if (first) {
          for (auto z : neighbors[i][idx]) {
            if (placed.find(z.first) == placed.end()) {
              poss.insert(z);
            }
          }
          first = false;
        } else {
          for (auto z : poss) {
            if (neighbors[i][idx].find(z) == neighbors[i][idx].end()) {
              poss.erase(z);
            }
          }
        }
      }
      i++;
    }

    if (poss.size() == 1) {
      grid[{y,x}] = *poss.begin();
      placed.insert(grid[{y,x}].first);
      for (auto o : adjacent) {
        int dy = o.first, dx = o.second;
        if (grid.find({y+dy,x+dx}) == grid.end()) {
          to_visit.insert({y+dy,x+dx});
        }
      }
    }
  }

  // for (int i = 0; i < 4; i++) delete neighbors[i];
  delete neighbors;

  // for (auto p : grid) {
  //   cout << p.first.first << ',' << p.first.second << ": " << p.second.first << ',' << p.second.second << endl;
  // }

  int ymin = INT_MAX, ymax = -INT_MAX;
  int xmin = INT_MAX, xmax = -INT_MAX;
  for (auto p : grid) {
    ymin = min(ymin, p.first.first);
    ymax = max(ymax, p.first.first);
    xmin = min(xmin, p.first.second);
    xmax = max(xmax, p.first.second);
  }

  // cout << "xmin: " << xmin << ", xmax: " << xmax << endl;
  // cout << "ymin: " << ymin << ", ymax: " << ymax << endl;

  // for (int y = ymin; y <= ymax; y++) {
  //   for (int x = xmin; x <= xmax; x++) {
  //     cout << grid[{y,x}].first << ' ';
  //   }
  //   cout << endl;
  // }

  int t = (ymax-ymin+1)*(d-2);
  bool ** total_grid = new bool*[t];
  for (int y = ymin; y <= ymax; y++) {
    for (int y2 = 1; y2 < d-1; y2++) {
      total_grid[(y-ymin)*(d-2)+y2-1] = new bool[t];
      for (int x = xmin; x <= xmax; x++) {
        for (int x2 = 1; x2 < d-1; x2++) {
          total_grid[(y-ymin)*(d-2)+y2-1][(x-xmin)*(d-2)+x2-1] = rotated_tiles[grid[{y,x}]][y2][x2];
        }
      }
    }
  }

  // cout << "t = " << t << endl;

  bool stop = false;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {

      // for (int y = 0; y < t; y++) {
      //   for (int x = 0; x < t; x++) {
      //     cout << (total_grid[y][x] ? '#' : '.');
      //   }
      //   cout << endl;
      // }
      // cout << "----------------------------" << endl;

      // Look for monsters
      for (int y = 0; y < t; y++) {
        if (y + mh >= t) continue;
        for (int x = 0; x < t; x++) {
          if (x + mw >= t) continue;

          bool success = true;
          for (auto o : monster) {
            int dy = o.first, dx = o.second;
            if (!total_grid[y+dy][x+dx]) {
              success = false;
              break;
            }
          }

          if (success) {
            // cout << "Found a monster at: " << y << ',' << x << endl;
            for (auto o : monster) {
              int dy = o.first, dx = o.second;
              total_grid[y+dy][x+dx] = false;
            }
            stop = true;
          }
        }
      }

      if (stop) {
        int ctr = 0;
        for (int y = 0; y < t; y++) {
          for (int x = 0; x < t; x++) {
            if (total_grid[y][x]) ctr++;
          }
        }
        cout << ctr << endl;
        break;
      }

      // Rotate
      for (int k = 0; k < (t+1)/2; k++) {
        for (int l = 0; l < (t+1)/2; l++) {
          bool tmp = total_grid[k][l];
          total_grid[k][l] = total_grid[l][t-1-k];
          total_grid[l][t-1-k] = total_grid[t-1-k][t-1-l];
          total_grid[t-1-k][t-1-l] = total_grid[t-1-l][k];
          total_grid[t-1-l][k] = tmp;
        }
      }
    }
    if (stop) break;

    // Reflect
    for (int k = 0; k < t; k++) {
      for (int l = 0; l < t/2; l++) {
        bool tmp = total_grid[k][l];
        total_grid[k][l] = total_grid[k][t-1-l];
        total_grid[k][t-1-l] = tmp;
      }
    }
  }

  // for (int i = 0; i < t; i++) delete total_grid[i];
  delete total_grid;

  // Delete the tiles
  for (auto p : rotated_tiles) {
    for (int y = 0; y < d; y++) delete rotated_tiles[p.first][y];
    delete rotated_tiles[p.first];
  }
}
