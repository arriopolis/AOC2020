#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n;
  vector<int> nums;
  while (cin >> n) {
    nums.push_back(n);
  }

  sort(nums.begin(), nums.end());

  int prev = 0;
  int diff1 = 0, diff3 = 1;
  for (int n : nums) {
    if (n - prev == 1) diff1++;
    else if (n - prev == 3) diff3++;
    prev = n;
  }

  cout << diff1 * diff3 << endl;
}
