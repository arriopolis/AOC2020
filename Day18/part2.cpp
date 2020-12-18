#include <iostream>
#include <string>
#include <vector>
using namespace std;

long long eval(string& s) {
  vector<pair<vector<long long>,char>> stack;
  stack.push_back({{1},'*'});
  bool expect_operator = false;
  long long a;
  for (char c : s) {
    if (c == ' ') continue;

    bool resolve = false;
    if (!expect_operator && c == '(') {
      stack.push_back({{1},'*'});
      continue;
    } else if (expect_operator && c == ')') {
      a = 1;
      for (long long f : stack.back().first) a *= f;
      stack.pop_back();
      resolve = true;
    } else if (expect_operator) {
      stack.back().second = c;
      expect_operator = false;
    } else {
      a = (long long)(c - '0');
      resolve = true;
    }

    if (resolve) {
      if (stack.back().second == '+') {
        stack.back().first.back() += a;
      } else if (stack.back().second == '*') {
        stack.back().first.push_back(a);
      } else {
        cout << "Unknown operator: " << stack.back().second << '.' << endl;
        return -1;
      }
      expect_operator = true;
    }
  }

  a = 1;
  for (long long f : stack.front().first) a *= f;
  return a;
}

int main() {
  string s;
  long long t = 0;
  while (getline(cin, s)) {
    t += eval(s);
  }
  cout << t << endl;
}
