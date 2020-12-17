#include <iostream>
#include <vector>
using namespace std;

int main() {
  string s;
  vector<string> input;
  while (getline(cin,s))
    input.push_back(s);

  int d = 1, h = input.size(), w = input[0].size();
  bool *** grid = new bool**[d];
  grid[0] = new bool*[h];
  for (int j = 0; j < h; j++) {
    grid[0][j] = new bool[w];
    for (int k = 0; k < w; k++) {
      grid[0][j][k] = (input[j][k] == '#');
    }
  }

  int iter = 0;

  bool changed = true;
  while (changed) {
    changed = false;

    // cout << "Depth: " << d << endl;
    // cout << "Height: " << h << endl;
    // cout << "Width: " << w << endl;
    cout << "Iteration: " << iter << endl;
    for (int i = 0; i < d; i++) {
      cout << "z = " << i << endl;
      for (int j = 0; j < h; j++) {
        for (int k = 0; k < w; k++)
          cout << (grid[i][j][k] ? '#' : '.');
        cout << endl;
      }
      cout << endl;
    }

    if (iter == 6) break;
    iter++;

    int oi = 0, oj = 0, ok = 0;
    int ei = 0, ej = 0, ek = 0;
    for (int j = 0; j < h; j++)
      for (int k = 0; k < w; k++) {
        if (grid[0][j][k]) oi = 1;
        if (grid[d-1][j][k]) ei = 1;
      }

    for (int i = 0; i < d; i++)
      for (int k = 0; k < w; k++) {
        if (grid[i][0][k]) oj = 1;
        if (grid[i][h-1][k]) ej = 1;
      }

    for (int i = 0; i < d; i++)
      for (int j = 0; j < h; j++) {
        if (grid[i][j][0]) ok = 1;
        if (grid[i][j][w-1]) ek = 1;
      }

    // cout << "oi: " << oi << ", ei: " << ei << endl;
    // cout << "oj: " << oj << ", ej: " << ej << endl;
    // cout << "ok: " << ok << ", ek: " << ek << endl;

    int newd = d + oi + ei, newh = h + oj + ej, neww = w + ok + ek;
    bool *** newgrid = new bool**[newd];
    for (int i = 0; i < newd; i++) {
      newgrid[i] = new bool*[newh];
      for (int j = 0; j < newh; j++) {
        newgrid[i][j] = new bool[neww];
        for (int k = 0; k < neww; k++) {
          int ctr = 0;
          for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
              for (int dk = -1; dk <= 1; dk++) {
                if (di == 0 && dj == 0 && dk == 0) continue;
                if (i+di-oi < 0 || i+di-oi >= d) continue;
                if (j+dj-oj < 0 || j+dj-oj >= h) continue;
                if (k+dk-ok < 0 || k+dk-ok >= w) continue;
                if (grid[i+di-oi][j+dj-oj][k+dk-ok]) ctr++;
              }
          bool prev = (i-oi >= 0 && i-oi < d && j-oj >= 0 && j-oj < h && k-ok >= 0 && k-ok < w && grid[i-oi][j-oj][k-ok]);
          newgrid[i][j][k] = (ctr == 3 || (ctr == 2 && prev));
          if (prev != newgrid[i][j][k]) changed = true;
        }
      }
    }

    for (int i = 0; i < d; i++) {
      for (int j = 0; j < h; j++) {
        delete grid[i][j];
      }
      delete grid[i];
    }
    delete grid;

    d = newd, h = newh, w = neww;
    grid = newgrid;
  }

  int ctr = 0;
  for (int i = 0; i < d; i++)
    for (int j = 0; j < h; j++)
      for (int k = 0; k < w; k++)
        if (grid[i][j][k]) ctr++;
  cout << ctr << endl;
}
