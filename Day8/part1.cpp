#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

int main() {
  string s;
  vector<pair<string,int>> program;
  while (getline(cin, s)) {
    istringstream iss(s);
    string instr, o;
    iss >> instr >> o;
    int op = stoi(o.substr(1));
    if (o[0] == '-') op *= -1;
    program.push_back({instr, op});
  }

  // for (auto p : program) {
  //   cout << p.first << ',' << p.second << endl;
  // }

  int accumulator = 0, idx = 0;
  set<int> visited;
  while (visited.find(idx) == visited.end()) {
    visited.insert(idx);
    string instr = program[idx].first;
    int op = program[idx].second;
    if (instr == "acc") {
      accumulator += op;
      idx++;
    } else if (instr == "jmp") {
      idx += op;
    } else if (instr == "nop") {
      idx++;
    }
  }

  cout << accumulator << endl;
}
