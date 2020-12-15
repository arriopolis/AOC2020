#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int LIM = 30000000;

int main() {
  string s;
  cin >> s;
  vector<int> ns;
  while (s.find(',') != -1) {
    ns.push_back(stoi(s.substr(0,s.find(','))));
    s = s.substr(s.find(',')+1);
  }
  ns.push_back(stoi(s));

  int * hist = new int[LIM];
  for (int i = 0; i < LIM; i++) hist[i] = -1;
  int i = 0;
  for (int n : ns) {
    hist[n] = i;
    i++;
  }

  int n = ns[ns.size()-1];
  while (i < LIM) {
    // if (i%100000 == 0) cout << ((double)i)/30000000 << endl;
    int newn;
    if (hist[n] != -1) {
      newn = i-hist[n]-1;
    } else {
      newn = 0;
    }
    hist[n] = i-1;
    i++;
    n = newn;
  }

  delete hist;

  cout << n << endl;
}
