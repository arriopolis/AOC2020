#include <iostream>
#include <map>
#include <vector>
#include <climits>
using namespace std;

const int PREAMBLE_SIZE = 25;

int main() {
  int n;
  vector<int> nums;
  while (cin >> n) {
    nums.push_back(n);
  }

  map<int,int> sums;
  for (int i = 0; i < PREAMBLE_SIZE; i++) {
    for (int j = 0; j < i; j++) {
      sums[nums[i] + nums[j]]++;
    }
  }

  int i = PREAMBLE_SIZE-1;
  while (++i < nums.size()) {
    if (sums[nums[i]] == 0) {
      n = nums[i];
      break;
    }
    for (int j = i - PREAMBLE_SIZE+1; j < i; j++) {
      if (--sums[nums[i - PREAMBLE_SIZE] + nums[j]] == 0) {
        sums.erase(nums[i - PREAMBLE_SIZE] + nums[j]);
      }
      sums[nums[i] + nums[j]]++;
    }
  }

  int imin = 0, imax = 2;
  int s = nums[0] + nums[1];
  while (imax < nums.size()) {
    if (s == n) break;
    while (s < n) s += nums[imax++];
    while (s > n) s -= nums[imin++];
  }

  int nmin = INT_MAX, nmax = 0;
  for (i = imin; i < imax; i++) {
    nmin = min(nmin, nums[i]);
    nmax = max(nmax, nums[i]);
  }

  cout << nmin + nmax << endl;
}
