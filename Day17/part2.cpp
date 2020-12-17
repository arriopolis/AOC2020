#include <iostream>
#include <vector>
using namespace std;

int main() {
  string s;
  vector<string> input;
  while (getline(cin,s))
    input.push_back(s);

  int c = 1, d = 1, h = input.size(), w = input[0].size();
  bool **** grid = new bool***[c];
  grid[0] = new bool**[d];
  grid[0][0] = new bool*[h];
  for (int k = 0; k < h; k++) {
    grid[0][0][k] = new bool[w];
    for (int l = 0; l < w; l++) {
      grid[0][0][k][l] = (input[k][l] == '#');
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
    for (int i = 0; i < c; i++) {
      for (int j = 0; j < d; j++) {
        cout << "z = " << i << ", w = " << j << endl;
        for (int k = 0; k < h; k++) {
          for (int l = 0; l < w; l++)
            cout << (grid[i][j][k][l] ? '#' : '.');
          cout << endl;
        }
        cout << endl;
      }
    }

    if (iter == 6) break;
    iter++;

    int oi = 0, oj = 0, ok = 0, ol = 0;
    int ei = 0, ej = 0, ek = 0, el = 0;
    for (int j = 0; j < c; j++)
      for (int k = 0; k < h; k++)
        for (int l = 0; l < w; l++) {
          if (grid[0][j][k][l]) oi = 1;
          if (grid[c-1][j][k][l]) ei = 1;
        }

    for (int i = 0; i < c; i++)
      for (int k = 0; k < h; k++)
        for (int l = 0; l < w; l++) {
          if (grid[i][0][k][l]) oj = 1;
          if (grid[i][d-1][k][l]) ej = 1;
        }

    for (int i = 0; i < c; i++)
      for (int j = 0; j < d; j++)
        for (int l = 0; l < w; l++) {
          if (grid[i][j][0][l]) ok = 1;
          if (grid[i][j][h-1][l]) ek = 1;
        }

    for (int i = 0; i < c; i++)
      for (int j = 0; j < d; j++)
        for (int k = 0; k < h; k++) {
          if (grid[i][j][k][0]) ol = 1;
          if (grid[i][j][k][w-1]) el = 1;
        }

    // cout << "oi: " << oi << ", ei: " << ei << endl;
    // cout << "oj: " << oj << ", ej: " << ej << endl;
    // cout << "ok: " << ok << ", ek: " << ek << endl;

    int newc = c + oi + ei, newd = d + oj + ej, newh = h + ok + ek, neww = w + ol + el;
    bool **** newgrid = new bool***[newc];
    for (int i = 0; i < newc; i++) {
      newgrid[i] = new bool**[newd];
      for (int j = 0; j < newd; j++) {
        newgrid[i][j] = new bool*[newh];
        for (int k = 0; k < newh; k++) {
          newgrid[i][j][k] = new bool[neww];
          for (int l = 0; l < neww; l++) {
            int ctr = 0;
            for (int di = -1; di <= 1; di++)
              for (int dj = -1; dj <= 1; dj++)
                for (int dk = -1; dk <= 1; dk++) {
                  for (int dl = -1; dl <= 1; dl++) {
                    if (di == 0 && dj == 0 && dk == 0 && dl == 0) continue;
                    if (i+di-oi < 0 || i+di-oi >= c) continue;
                    if (j+dj-oj < 0 || j+dj-oj >= d) continue;
                    if (k+dk-ok < 0 || k+dk-ok >= h) continue;
                    if (l+dl-ol < 0 || l+dl-ol >= w) continue;
                    if (grid[i+di-oi][j+dj-oj][k+dk-ok][l+dl-ol]) ctr++;
                  }
                }
            bool prev = (i-oi >= 0 && i-oi < c && j-oj >= 0 && j-oj < d && k-ok >= 0 && k-ok < h && l-ol >= 0 && l-ol < w && grid[i-oi][j-oj][k-ok][l-ol]);
            newgrid[i][j][k][l] = (ctr == 3 || (ctr == 2 && prev));
            if (prev != newgrid[i][j][k][l]) changed = true;
          }
        }
      }
    }

    for (int i = 0; i < c; i++) {
      for (int j = 0; j < d; j++) {
        for (int k = 0; k < h; k++)
          delete grid[i][j][k];
        delete grid[i][j];
      }
      delete grid[i];
    }
    delete grid;

    c = newc, d = newd, h = newh, w = neww;
    grid = newgrid;
  }

  int ctr = 0;
  for (int i = 0; i < c; i++)
    for (int j = 0; j < d; j++)
      for (int k = 0; k < h; k++)
        for (int l = 0; l < w; l++)
          if (grid[i][j][k][l]) ctr++;
  cout << ctr << endl;
}
