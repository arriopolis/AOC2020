#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
using namespace std;

bool run_code(vector<pair<string,int>> program, int idx, int accumulator, set<int> visited, bool changed) {
  while (visited.find(idx) == visited.end()) {
    if (idx == program.size()) {
      cout << accumulator << endl;
      return true;
    }
    visited.insert(idx);
    string instr = program[idx].first;
    int op = program[idx].second;
    if (instr == "acc") {
      accumulator += op;
      idx++;
    } else if (instr == "jmp") {
      if (!changed && run_code(program, idx+1, accumulator, visited, true)) return true;
      idx += op;
    } else if (instr == "nop") {
      if (!changed && run_code(program, idx + op, accumulator, visited, true)) return true;
      idx++;
    }
  }
  return false;
}

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

  run_code(program, 0, 0, {}, false);
}
