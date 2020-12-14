#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main() {
  long long or_mask;
  vector<long long> float_masks = {0};
  map<long long, long long> mem;
  string s;
  while (getline(cin,s)) {
    // cout << s << endl;
    if (s.substr(0,4) == "mask") {

      or_mask = 0;
      float_masks = {0};

      for (char c : s.substr(7)) {
        or_mask <<= 1;
        if (c == '1') or_mask++;

        vector<long long> new_float_masks;
        for (long long fm : float_masks) {
          fm <<= 1;
          new_float_masks.push_back(fm);
          if (c == 'X') {
            new_float_masks.push_back(fm+1);
          }
        }
        float_masks = new_float_masks;
      }

      // cout << "Or mask:" << or_mask << endl;
      // cout << "Float masks:" << endl;
      // for (long long fm : float_masks) {
      //   cout << fm << endl;
      // }
    } else if (s.substr(0,3) == "mem") {
      long long loc = stoll(s.substr(4, s.find(']'))) | or_mask;
      // cout << loc << endl;
      long long val = stoll(s.substr(s.find('=')+2));
      for (long long fm : float_masks) {
        mem[loc ^ fm] = val;
      }

      // cout << "Memory:" << endl;
      // for (auto p : mem) {
      //   cout << p.first << " : " << p.second << endl;
      // }
    }
  }
  long long t = 0;
  for (auto p : mem) {
    t += p.second;
  }
  cout << t << endl;
}
