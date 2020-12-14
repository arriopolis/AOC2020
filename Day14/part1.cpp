#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
  long long and_mask;
  long long or_mask;
  map<int, long long> mem;
  string s;
  while (getline(cin,s)) {
    if (s.substr(0,4) == "mask") {
      and_mask = 0;
      or_mask = 0;
      for (char c : s.substr(7)) {
        and_mask <<= 1;
        or_mask <<= 1;
        if (c == '1') or_mask++;
        else if (c != '0') and_mask++;
      }
    } else if (s.substr(0,3) == "mem") {
      int loc = stoi(s.substr(4, s.find(']')));
      mem[loc] = (stoll(s.substr(s.find('=')+2)) & and_mask) | or_mask;
    }
  }
  long long t = 0;
  for (auto p : mem) {
    t += p.second;
  }
  cout << t << endl;
}
