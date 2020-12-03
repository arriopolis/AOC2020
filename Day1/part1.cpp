#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
  set<int> nums;

  int n;
  while (cin >> n) nums.insert(n);

  for (int n : nums) {
    if (nums.find(2020 - n) != nums.end()) {
      cout << n * (2020 - n) << endl;
      break;
    }
  }
}
