#include <iostream>
#include <string>
#include <list>
using namespace std;

const int NUM_MOVES = 10000000;
const int NUM_CUPS = 1000000;

// const int NUM_MOVES = 100;
// const int NUM_CUPS = 9;

int main() {
  string s;
  cin >> s;
  list<int> cups;
  for (char c : s) {
    cups.push_back(c - '0');
  }
  for (int i = cups.size()+1; i <= NUM_CUPS; i++) {
    cups.push_back(i);
  }

  list<int>::iterator * poss = new list<int>::iterator[NUM_CUPS];
  for (auto it = cups.begin(); it != cups.end(); it++) {
    poss[*it-1] = it;
  }

  auto src = cups.begin();
  for (int a = 0; a < NUM_MOVES; a++) {

    // cout << "Poss: ";
    // for (int i = 0; i < NUM_CUPS; i++) {
    //   cout << *poss[i] << ' ';
    // }
    // cout << endl;

    // cout << "Cups: ";
    // for (int x : cups) cout << x << ' ';
    // cout << endl;

    int val = *(src++);
    if (src == cups.end()) src = cups.begin();

    // cout << "Value: " << val << endl;

    list<int> pick_up;
    for (int i = 0; i < 3; i++) {
      poss[*src-1] = cups.end();
      pick_up.push_back(*src);
      src = cups.erase(src);
      if (src == cups.end()) src = cups.begin();
    }

    // cout << "Pick up: ";
    // for (auto x : pick_up) cout << x << ' ';
    // cout << endl;

    int i = (val+NUM_CUPS-2)%NUM_CUPS+1;
    while (poss[i-1] == cups.end()) {
      i = (i+NUM_CUPS-2)%NUM_CUPS+1;
    }

    auto dest = poss[i-1];
    // cout << "Destination number: " << *dest << endl;

    if (++dest == cups.end()) dest = cups.begin();
    for (auto it = pick_up.begin(); it != pick_up.end(); it++) {
      poss[*it-1] = cups.insert(dest, *it);
    }
  }

  // cout << "Cups: ";
  // for (int x : cups) cout << x << ' ';
  // cout << endl;

  long long f = 1;
  auto it = poss[0];
  if (++it == cups.end()) it = cups.begin();
  f *= *it;
  if (++it == cups.end()) it = cups.begin();
  f *= *it;
  cout << f << endl;

  delete[] poss;
}
