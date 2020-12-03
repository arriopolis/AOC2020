#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  set<int> nums;

  int n;
  while (cin >> n) nums.insert(n);

  for (int n1 : nums) {
    for (int n2 : nums) {
      if (nums.find(2020 - n1 - n2) != nums.end()) {
        cout << n1 * n2 * (2020 - n1 - n2) << endl;
        exit(0);
      }
    }
  }
}
