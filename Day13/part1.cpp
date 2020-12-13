#include <iostream>
#include <string>
#include <set>
#include <climits>
using namespace std;

int main() {
  int t;
  cin >> t;

  set<int> ids;
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
    if (s2 == "x") continue;
    ids.insert(stoi(s2));
  }

  int min_t = INT_MAX;
  int min_id = 0;
  for (int id : ids) {
    int new_t = id-(t%id);
    if (new_t < min_t) {
      min_t = new_t;
      min_id = id;
    }
  }
  cout << min_id * min_t << endl;
}
