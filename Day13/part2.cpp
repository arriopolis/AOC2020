#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <tuple>
using namespace std;

tuple<long long, long long, long long> e_gcd(long long a, long long b) {
  long long old_r = a, r = b;
  long long old_s = 1, s = 0;
  long long old_t = 0, t = 1;
  while (r != 0) {
    long long q = old_r / r;

    long long tmp_r = old_r - q*r;
    old_r = r;
    r = tmp_r;

    long long tmp_s = old_s - q*s;
    old_s = s;
    s = tmp_s;

    long long tmp_t = old_t - q*t;
    old_t = t;
    t = tmp_t;
  }

  return {old_s, old_t, old_r};
}

int main() {
  int t;
  cin >> t;

  vector<int> ids;
  string s;
  cin >> s;
  while (s.size() > 0) {
    string s2;
    if (s.find(',') == -1) {
      s2 = s;
      s = "";
    } else {
      s2 = s.substr(0, s.find(','));
      s = s.substr(s.find(',')+1);
    }
    // cout << s2 << ' ';
    if (s2 == "x") {
      ids.push_back(-1);
    } else {
      ids.push_back(stoi(s2));
    }
  }
  // cout << endl;

  long long period = 1;
  long long offset = 0;
  int ctr = 0;
  for (int id : ids) {
    if (id != -1) {
      tuple<long long, long long, long long> tpl = e_gcd(period, id);
      long long a = get<0>(tpl), b = get<1>(tpl), g = get<2>(tpl);
      a = -a*(ctr-(id-offset%id))/g;
      b = -b*(ctr-(id-offset%id))/g;
      offset += a*period;

      period = period * id / g;
      while (offset < 0) offset += period;
      while (offset >= period) offset -= period;

      // cout << "ID:" << id << endl;
      // cout << "Period:" << period << endl;
      // cout << "Offset:" << offset << endl;
    }
    ctr++;
  }

  cout << offset << endl;
}
