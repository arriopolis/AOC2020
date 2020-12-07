#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
using namespace std;

int main() {
  string rule;
  map<string,map<string,int>> graph;
  while (getline(cin, rule)) {
    istringstream iss(rule);
    string s,s1,s2;
    iss >> s1 >> s2 >> s >> s;
    string color = s1 + " " + s2;
    int i;
    while (iss >> i) {
      iss >> s1 >> s2 >> s;
      string child_color = s1 + " " + s2;
      graph[color][child_color] = i;
    }
  }

  map<string,map<string,int>> reverse_graph;
  for (auto p : graph) {
    for (auto q : p.second) {
      reverse_graph[q.first][p.first] = q.second;
    }
  }

  // for (auto p : reverse_graph) {
  //   cout << p.first << " : ";
  //   for (auto q : p.second) {
  //     cout << q.first << ',' << q.second << ' ';
  //   }
  //   cout << endl;
  // }

  set<string> to_visit;
  set<string> parents;
  to_visit.insert("shiny gold");
  while (!to_visit.empty()) {
    auto pcolor = to_visit.begin();
    string color = *pcolor;
    to_visit.erase(pcolor);

    for (auto p : reverse_graph[color]) {
      parents.insert(p.first);
      to_visit.insert(p.first);
    }
  }

  cout << parents.size() << endl;
}
