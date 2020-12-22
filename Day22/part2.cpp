#include <iostream>
#include <string>
#include <deque>
#include <set>
using namespace std;

bool recursive_combat(deque<int>& stack1, deque<int>& stack2) {
  // cout << "Playing recursive combat:" << endl;
  // cout << "Stack 1: ";
  // for (auto x : stack1) cout << x << ' ';
  // cout << endl;
  // cout << "Stack 2: ";
  // for (auto x : stack2) cout << x << ' ';
  // cout << endl;

  set<pair<deque<int>,deque<int>>> visited;
  while (stack1.size() > 0 && stack2.size() > 0) {
    if (visited.find({stack1, stack2}) != visited.end()) return true;
    visited.insert({stack1, stack2});

    int a = stack1.front(), b = stack2.front();
    stack1.pop_front(), stack2.pop_front();

    bool win;
    if (stack1.size() >= a && stack2.size() >= b) {
      deque<int> new_stack1, new_stack2;
      auto it1 = stack1.begin(), it2 = stack2.begin();
      for (int i = 0; i < a; i++) new_stack1.push_back(*(it1++));
      for (int i = 0; i < b; i++) new_stack2.push_back(*(it2++));
      win = recursive_combat(new_stack1, new_stack2);
    } else {
      win = (a > b);
    }

    if (win) {
      stack1.push_back(a);
      stack1.push_back(b);
    } else {
      stack2.push_back(b);
      stack2.push_back(a);
    }
  }

  // cout << "Winner: " << (stack1.size() > 0 ? "Player 1" : "Player 2") << endl;
  // cout << "Final stack 1: ";
  // for (auto x : stack1) cout << x << ' ';
  // cout << endl;
  // cout << "Final stack 2: ";
  // for (auto x : stack2) cout << x << ' ';
  // cout << endl;

  return (stack1.size() > 0);
}

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

  bool win = recursive_combat(stack1, stack2);

  int i = 0;
  long long t = 0;
  deque<int>& stack = (win ? stack1 : stack2);
  while (stack.size() > 0) {
    t += (++i) * stack.back();
    stack.pop_back();
  }
  cout << t << endl;
}
