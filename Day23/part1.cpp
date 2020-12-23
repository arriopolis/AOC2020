#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int NUM_MOVES = 100;

int main() {
  string s;
  cin >> s;
  vector<int> cups;
  for (char c : s) {
    cups.push_back(c - '0');
  }

  int i = 0;
  for (int a = 0; a < NUM_MOVES; a++) {

    // for (int x : cups) cout << x << ' ';
    // cout << endl;
    // cout << "Value: " << cups[i] << endl;

    vector<int> pick_up;
    for (int j = 0; j < 3; j++) {
      int pos = (i+1)%cups.size();
      if (pos == 0) i--;
      pick_up.push_back(cups[pos]);
      cups.erase(cups.begin()+pos);
    }

    // cout << "Pick up: ";
    // for (int x : pick_up) cout << x << ' ';
    // cout << endl;
    // for (int x : cups) cout << x << ' ';
    // cout << endl;

    int dest = 0;
    for (int j = 1; j < cups.size(); j++) {
      if (cups[j] < cups[i] && (cups[j] > cups[dest] || cups[dest] >= cups[i])) {
        dest = j;
      } else if (cups[j] > cups[dest] && cups[dest] >= cups[i]) {
        dest = j;
      }
    }
    dest = (dest+1)%cups.size();
    // cout << "Destination: " << dest << endl;

    for (int j = 0; j < 3; j++) {
      cups.insert(cups.begin()+dest, pick_up.back());
      pick_up.pop_back();
    }

    if (dest <= i) i += 3;
    i = (i+1)%cups.size();
  }

  bool print = false;
  for (int i = 0; i < 2*cups.size(); i++) {
    if (print && cups[i%cups.size()] == 1) break;
    if (print) cout << cups[i%cups.size()];
    if (!print && cups[i%cups.size()] == 1) print = true;
  }
  cout << endl;
}
