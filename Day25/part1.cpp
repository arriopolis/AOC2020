#include <iostream>
using namespace std;

const long long MOD = 20201227;

int main() {
  long long a,b;
  cin >> a >> b;

  long long s = 7, v = 1, i = 0;
  while (v != a && v != b) {
    v = (v*s)%MOD;
    i++;
  }
  if (v == a) s = b;
  else s = a;
  v = 1;
  while (i > 0) {
    v = (v*s)%MOD;
    i--;
  }
  cout << v << endl;
}
