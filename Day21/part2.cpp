#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
  string s;
  vector<pair<set<string>, set<string>>> foods;
  while (getline(cin, s)) {
    set<string> ingredients;
    set<string> allergens;
    bool allergens_present = false;
    while (s.find(' ') != -1) {
      if (s[0] == '(') {
        s = s.substr(10, s.size()-11);
        allergens_present = true;
        break;
      }
      ingredients.insert(s.substr(0,s.find(' ')));
      s = s.substr(s.find(' ')+1);
    }
    if (!allergens_present) {
      ingredients.insert(s);
    } else {
      while (s.find(", ") != -1) {
        allergens.insert(s.substr(0, s.find(", ")));
        s = s.substr(s.find(", ")+2);
      }
      allergens.insert(s);
    }
    foods.push_back({ingredients, allergens});
  }

  for (auto p : foods) {
    for (string x : p.first) cout << x << ' ';
    cout << "- ";
    for (string x : p.second) cout << x << ' ';
    cout << endl;
  }

  set<string> allergens;
  set<string> ingredients;
  for (auto p : foods) {
    for (string i : p.first) {
      ingredients.insert(i);
    }
    for (string a : p.second) {
      allergens.insert(a);
    }
  }

  set<string> used;
  vector<string> dict;
  bool changed = true;
  while (changed) {
    changed = false;
    set<string> new_allergens;
    for (string a : allergens) {
      bool first = true;
      set<string> poss;
      for (auto p : foods) {
        if (p.second.find(a) == p.second.end()) continue;
        if (first) {
          for (string i : p.first) {
            if (used.find(i) == used.end()) {
              poss.insert(i);
            }
          }
        } else {
          set<string> new_poss;
          for (string i : poss) {
            if (p.first.find(i) != p.first.end()) {
              new_poss.insert(i);
            }
          }
          poss = new_poss;
        }
        first = false;
      }
      if (poss.size() == 1) {
        string i = *poss.begin();
        used.insert(i);
        dict.push_back(a + "-" + i);
        changed = true;
      } else {
        new_allergens.insert(a);
      }
    }
    allergens = new_allergens;
  }

  for (auto i : used) {
    cout << i << endl;
  }

  sort(dict.begin(), dict.end());

  for (auto i : dict) {
    cout << i.substr(i.find('-')+1) << ',';
  }
  cout << endl;
}
