#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <set>
#include <vector>
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

  // for (auto p : graph) {
  //   cout << p.first << " : ";
  //   for (auto q : p.second) {
  //     cout << q.first << ',' << q.second << ' ';
  //   }
  //   cout << endl;
  // }
  // cout << endl;

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
  // cout << endl;

  set<string> heads;
  for (auto p : graph) {
    if (reverse_graph[p.first].size() == 0) {
      heads.insert(p.first);
    }
  }

  vector<string> order;
  while (!heads.empty()) {
    string color = *heads.begin();
    heads.erase(color);
    order.push_back(color);

    for (auto p : graph[color]) {
      reverse_graph[p.first].erase(color);
      if (reverse_graph[p.first].size() == 0) {
        heads.insert(p.first);
      }
    }
  }

  // for (string color : order) {
  //   cout << color << ',';
  // }
  // cout << endl;

  map<string,int> req;
  req["shiny gold"] = 1;
  for (string color : order) {
    if (req[color] == 0) continue;
    for (auto p : graph[color]) {
      req[p.first] += req[color] * p.second;
    }
  }

  int ctr = 0;
  for (auto p : req) {
    ctr += p.second;
  }
  cout << ctr-1 << endl;
}
