#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

const int poss_length = 8;

int main() {
  string s;
  map<int,set<vector<int>>> g;
  map<int,vector<string>> a;
  while (getline(cin,s)) {
    if (s.size() == 0) break;
    int rule = stoi(s.substr(0,s.find(':')));
    s = s.substr(s.find(':')+2);
    if (s[0] == '"') {
      s = s.substr(1,s.size()-2);
      a[rule].push_back(s);
    } else {
      vector<int> l;
      while (s.find(' ') != -1) {
        if (s[0] == '|') {
          g[rule].insert(l);
          l.clear();
        } else l.push_back(stoi(s.substr(0,s.find(' '))));
        s = s.substr(s.find(' ')+1);
      }
      l.push_back(stoi(s));
      g[rule].insert(l);
    }
  }

  g[8] = {{42}, {42,8}};
  g[11] = {{42,31}, {42,11,31}};

  set<string> v;
  while (getline(cin,s)) {
    v.insert(s);
  }

  for (auto p : g) {
    cout << p.first << ": ";
    for (auto i : p.second) {
      for (auto j : i) cout << j << ' ';
      cout << ", ";
    }
    cout << endl;
  }

  for (auto p : a) {
    cout << p.first << ": ";
    for (string s : p.second) {
      cout << s << ", ";
    }
    cout << endl;
  }

  bool changed = true;
  while (changed) {
    changed = false;
    for (auto p : g) {
      if (a.find(p.first) != a.end()) continue;

      bool loop = false;
      for (auto i : p.second) {
        if (find(i.begin(), i.end(), p.first) != i.end()) {
          loop = true;
          break;
        }
      }
      if (loop) continue;

      bool success = true;
      for (auto i : p.second) {
        for (int j : i) {
          if (a.find(j) == a.end()) {
            success = false;
            break;
          }
        }
      }

      if (success) {
        changed = true;
        vector<string> pos;
        for (auto i : p.second) {
          int f = 1;
          for (int j : i) f *= a[j].size();

          for (int k = 0; k < f; k++) {
            string t = "";
            int l = k;
            for (int j : i) {
              t += a[j][l%a[j].size()];
              l /= a[j].size();
            }
            pos.push_back(t);
          }

        }
        a[p.first] = pos;
      }
    }
  }

  for (auto p : a) {
    cout << p.first << ": ";
    for (string s : p.second) {
      cout << s << ", ";
    }
    cout << endl;
  }

  int ctr = 0;
  for (string t : v) {
    int ctr42 = 0, ctr31 = 0;
    string tmp = t;
    while (t.size() >= 2*poss_length && find(a[42].begin(), a[42].end(), t.substr(0,poss_length)) != a[42].end()) {
      t = t.substr(poss_length);
      ctr42++;
    }
    while (t.size() >= poss_length && find(a[31].begin(), a[31].end(), t.substr(0,poss_length)) != a[31].end()) {
      t = t.substr(poss_length);
      ctr31++;
    }
    if (t.size() == 0 && ctr42 > ctr31 && ctr31 >= 1) {
      for (int i = 0; i < ctr42; i++) cout << "42, ";
      for (int i = 0; i < ctr31; i++) cout << "31, ";
      cout << endl;
      ctr++;
    }
  }
  cout << ctr << endl;
}
