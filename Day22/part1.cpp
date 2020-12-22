#include <iostream>
#include <string>
#include <deque>
using namespace std;

int main() {
  string s;
  deque<int> stack1;
  deque<int> stack2;

  getline(cin,s);
  while (getline(cin, s)) {
    if (s.size() == 0) break;
    stack1.push_back(stoi(s));
  }
  getline(cin,s);
  while (getline(cin, s)) {
    stack2.push_back(stoi(s));
  }

  while (stack1.size() > 0 && stack2.size() > 0) {
    int a = stack1.front(), b = stack2.front();
    stack1.pop_front(), stack2.pop_front();

    if (a > b) {
      stack1.push_back(a);
      stack1.push_back(b);
    } else {
      stack2.push_back(b);
      stack2.push_back(a);
    }
  }

  int i = 0;
  long long t = 0;
  deque<int>& stack = (stack1.size() > 0 ? stack1 : stack2);
  while (stack.size() > 0) {
    t += (++i) * stack.back();
    stack.pop_back();
  }
  cout << t << endl;
}
