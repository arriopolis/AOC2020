#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

int main() {
  map<string,set<pair<int,int>>> fields;
  string s;
  while (getline(cin, s)) {
    if (s.size() == 0) break;
    string field = s.substr(0,s.find(':'));
    s = s.substr(s.find(':')+2);
    while (s.find(" or ") != -1) {
      string range = s.substr(0,s.find(" or "));
      s = s.substr(s.find(" or ")+4);
      int l = stoi(range.substr(0,s.find('-')));
      range = range.substr(range.find('-')+1);
      int u = stoi(range);
      fields[field].insert({l,u});
    }
    int l = stoi(s.substr(0,s.find('-')));
    s = s.substr(s.find('-')+1);
    int u = stoi(s);
    fields[field].insert({l,u});
  }

  // for (auto p : fields) {
  //   cout << p.first << ": ";
  //   for (auto q : p.second) {
  //     cout << q.first << '-' << q.second << ' ';
  //   }
  //   cout << endl;
  // }

  getline(cin,s);
  getline(cin,s);
  set<int> your_values;
  while (s.find(',') != -1) {
    your_values.insert(stoi(s.substr(0,s.find(','))));
    s = s.substr(s.find(',')+1);
  }
  your_values.insert(stoi(s));

  // for (int v : your_values) {
  //   cout << v << ' ';
  // }
  // cout << endl;

  getline(cin,s);
  getline(cin,s);
  vector<set<int>> nearby_values;
  while (getline(cin,s)) {
    set<int> nearby;
    while (s.find(',') != -1) {
      nearby.insert(stoi(s.substr(0,s.find(','))));
      s = s.substr(s.find(',')+1);
    }
    nearby.insert(stoi(s));
    nearby_values.push_back(nearby);
  }

  int t = 0;
  for (auto x : nearby_values) {
    for (int v : x) {
      bool success = false;
      for (auto p : fields) {
        for (auto q : p.second) {
          if (q.first <= v && v <= q.second) {
            success = true;
            break;
          }
        }
        if (success) break;
      }
      if (!success) {
        // cout << v << endl;
        t += v;
      }
    }
  }

  cout << t << endl;
}
