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

  long long poss[nums.size()+1];
  poss[0] = 1;
  for (int i = 0; i < nums.size(); i++) {
    n = nums[i];
    long long tot = 0;
    if (n <= 3) tot++;
    for (int j = i-1; j >= 0; j--) {
      if (n - nums[j] <= 3) {
        tot += poss[j+1];
      }
    }
    poss[i+1] = tot;
  }

  cout << poss[nums.size()] << endl;
}
