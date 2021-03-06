#include <iostream>
#include <string>
#include <vector>
#include <map>
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

  map<int,int> hist;
  int i = 0;
  for (int n : ns) {
    hist[n] = i;
    i++;
  }

  int n;
  while (i <= 2020) {
    n = ns[ns.size()-1];
    int newn;
    if (hist.find(n) != hist.end()) {
      newn = i-hist[n]-1;
    } else {
      newn = 0;
    }
    ns.push_back(newn);
    hist[n] = i-1;
    i++;
  }

  cout << n << endl;
}
