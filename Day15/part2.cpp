#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
  string s;
  cin >> s;
  vector<int> ns;
  while (s.find(',') != -1) {
    ns.push_back(stoi(s.substr(0,s.find(','))));
    s = s.substr(s.find(',')+1);
  }
  ns.push_back(stoi(s));

  unordered_map<int,int> hist;
  int i = 0;
  for (int n : ns) {
    hist[n] = i;
    i++;
  }

  int n = ns[ns.size()-1];
  while (i < 30000000) {
    // if (i%100000 == 0) cout << ((double)i)/30000000 << endl;
    int newn;
    if (hist.find(n) != hist.end()) {
      newn = i-hist[n]-1;
    } else {
      newn = 0;
    }
    hist[n] = i-1;
    i++;
    n = newn;
  }

  cout << n << endl;
}
