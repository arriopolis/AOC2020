#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  string s;
  set<char> questions;
  bool first = true;
  int ctr = 0;
  while (getline(cin,s)) {
    if (s.size() == 0) {
      // cout << questions.size() << " : ";
      // for (char c : questions) {
      //   cout << c;
      // }
      // cout << endl;
      ctr += questions.size();
      questions.clear();
      first = true;
      continue;
    }
    if (first) {
      for (char c : s) {
        questions.insert(c);
      }
    } else {
      set<char> new_questions;
      for (char c : s) {
        new_questions.insert(c);
      }
      set<char>::iterator it = questions.begin();
      while (it != questions.end()) {
        char c = *(it++);
        if (new_questions.find(c) == new_questions.end()) {
          questions.erase(c);
        }
      }
    }
    first = false;
  }
  ctr += questions.size();

  cout << ctr << endl;
}
