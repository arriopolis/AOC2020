#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  string s;
  set<char> questions;
  int ctr = 0;
  while (getline(cin,s)) {
    if (s.size() == 0) {
      ctr += questions.size();
      questions.clear();
      continue;
    }
    for (char c : s) {
      questions.insert(c);
    }
  }
  ctr += questions.size();

  cout << ctr << endl;
}
