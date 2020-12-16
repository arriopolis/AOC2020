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
  vector<int> your_values;
  while (s.find(',') != -1) {
    your_values.push_back(stoi(s.substr(0,s.find(','))));
    s = s.substr(s.find(',')+1);
  }
  your_values.push_back(stoi(s));

  // for (int v : your_values) {
  //   cout << v << ' ';
  // }
  // cout << endl;

  getline(cin,s);
  getline(cin,s);
  vector<vector<int>> nearby_values;
  while (getline(cin,s)) {
    vector<int> nearby;
    while (s.find(',') != -1) {
      nearby.push_back(stoi(s.substr(0,s.find(','))));
      s = s.substr(s.find(',')+1);
    }
    nearby.push_back(stoi(s));
    nearby_values.push_back(nearby);
  }

  map<string,set<int>> posss;
  for (auto p : fields) {
    for (int i = 0; i < your_values.size(); i++) {
      posss[p.first].insert(i);
    }
  }

  int t = 0;
  bool success;
  for (auto x : nearby_values) {
    for (int v : x) {
      success = false;
      for (auto p : fields) {
        for (auto q : p.second) {
          if (q.first <= v && v <= q.second) {
            success = true;
            break;
          }
        }
        if (success) break;
      }
      if (!success) break;
    }
    if (!success) {
      // for (int v : x) {
      //   cout << v << ' ';
      // }
      // cout << endl;
      // cout << "This ticket is invalid." << endl;
      continue;
    }

    int i = 0;
    for (int v : x) {
      // cout << "Checking: " << v << endl;
      for (auto p : posss) {
        if (p.second.find(i) != p.second.end()) {
          bool success = false;
          for (auto q : fields[p.first]) {
            if (q.first <= v && v <= q.second) {
              success = true;
              break;
            }
          }
          if (!success) {
            // cout << "Removing " << i << " from " << p.first << endl;
            posss[p.first].erase(i);
          }
        }
      }
      i++;
    }
  }

  // for (auto p : posss) {
  //   cout << p.first << ": ";
  //   for (int q : p.second) {
  //     cout << q << ' ';
  //   }
  //   cout << endl;
  // }

  vector<string> order(your_values.size());
  while (posss.size() > 0) {
    for (auto p : posss) {
      if (p.second.size() == 1) {
        int pos = *p.second.begin();
        order[pos] = p.first;
        // cout << p.first << ": " << pos << endl;
        posss.erase(p.first);
        for (auto q : posss) {
          if (posss[q.first].find(pos) != posss[q.first].end()) {
            posss[q.first].erase(pos);
          }
        }

        // for (auto p : posss) {
        //   cout << p.first << ": ";
        //   for (int q : p.second) {
        //     cout << q << ' ';
        //   }
        //   cout << endl;
        // }

        break;
      }
    }
  }

  // for (string t : order) {
  //   cout << t << ", ";
  // }
  // cout << endl;

  int i = 0;
  long long f = 1;
  for (string t : order) {
    if (t.substr(0,9) == "departure") {
      // cout << i << endl;
      f *= your_values[i];
      // cout << f << endl;
    }
    i++;
  }

  cout << f << endl;
}
