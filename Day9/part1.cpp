#include <iostream>
#include <map>
#include <vector>
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

    // for (auto p : sums) {
    //   cout << p.first << ',' << p.second << ' ';
    // }
    // cout << endl;

    if (sums[nums[i]] == 0) {
      cout << nums[i] << endl;
      return 0;
    }
    for (int j = i - PREAMBLE_SIZE+1; j < i; j++) {
      if (--sums[nums[i - PREAMBLE_SIZE] + nums[j]] == 0) {
        sums.erase(nums[i - PREAMBLE_SIZE] + nums[j]);
      }
      sums[nums[i] + nums[j]]++;
    }
  }
}
