#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

using namespace std;

// 非负数组前k个最小的子序列累加和
// 给定一个数组nums，含有n个数字，都是非负数
// 给定一个正数k，返回所有子序列中累加和最小的前k个累加和
// 子序列是包含空集的
// 1 <= n <= 10^5
// 1 <= nums[i] <= 10^6
// 1 <= k <= 10^5
// 注意这个数据量，用01背包的解法是不行的，时间复杂度太高了
// 对数器验证

// 暴力方法
// 得到所有子序列的和
void f1(vector<int> &nums, int index, int sum, vector<int> &ans) {
  if (index == nums.size()) {
    ans.push_back(sum);
  } else {
    f1(nums, index + 1, sum, ans);
    f1(nums, index + 1, sum + nums[index], ans);
  }
}

// 暴力方法
// 为了验证
vector<int> topKSum1(vector<int> &nums, int k) {
  vector<int> allSubsequences;
  f1(nums, 0, 0, allSubsequences);
  sort(allSubsequences.begin(), allSubsequences.end());

  return vector<int>(allSubsequences.begin(), allSubsequences.begin() + k);
}

// 01背包来实现
// 这种方法此时不是最优解
// 因为n很大，数值也很大，那么可能的累加和就更大
// 时间复杂度太差
vector<int> topKSum2(vector<int> &nums, int k) {
  int sum = accumulate(nums.begin(), nums.end(), 0);

  // dp[i][j]
  // 1) dp[i-1][j]
  // 2) dp[i-1][j-nums[i]]
  vector<int> dp(sum + 1);
  dp[0] = 1;

  for (int num : nums) {
    for (int j = sum; j >= num; --j) {
      dp[j] += dp[j - num];
    }
  }

  int index = 0;
  vector<int> ans(k);
  for (int j = 0; j <= sum && index < k; ++j) {
    for (int i = 0; i < dp[j] && index < k; ++i) {
      ans[index++] = j;
    }
  }

  return ans;
}

// 正式方法
// 用堆来做是最优解，时间复杂度O(n * log n) + O(k * log k)
vector<int> topKSum3(vector<int> &nums, int k) {
  sort(nums.begin(), nums.end());

  // (子序列的最右下标，子序列的累加和)
  auto comp = [](pair<int, int> &p1, pair<int, int> &p2) noexcept {
    return p1.second > p2.second;
  };

  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> heap(comp);
  heap.emplace(0, nums[0]);

  vector<int> ans(k);
  for (int i = 1; i < k; ++i) {
    auto cur = heap.top();
    heap.pop();
    int right = cur.first;
    int sum = cur.second;
    ans[i] = sum;

    if (right + 1 < nums.size()) {
      heap.emplace(right + 1, sum - nums[right] + nums[right + 1]);
      heap.emplace(right + 1, sum + nums[right + 1]);
    }
  }

  return ans;
}

vector<int> randomArray(int len, int value) {
  vector<int> ans(len);
  for (int i = 0; i < len; i++) {
    ans[i] = rand() % value;
  }
  return ans;
}

bool equals(vector<int> &ans1, vector<int> &ans2) {
  if (ans1.size() != ans2.size()) {
    return false;
  }
  for (int i = 0; i < ans1.size(); i++) {
    if (ans1[i] != ans2[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int n = 10;
  int v = 40;
  int testTime = 5000;
  cout << "Testing started" << endl;
  for (int i = 0; i < testTime; i++) {
    int len = rand() % n + 1;
    vector<int> nums = randomArray(len, v);
    vector<int> nums2 = nums;
    vector<int> nums3 = nums;

    int k = rand() % ((1 << len) - 1) + 1;
    vector<int> ans1 = topKSum1(nums, k);
    vector<int> ans2 = topKSum2(nums2, k);
    vector<int> ans3 = topKSum3(nums3, k);

    if (!equals(ans1, ans2) || !equals(ans1, ans3)) {
      cout << "Error!" << endl;
    }
  }

  cout << "Testing finished" << endl;
  return 0;
}

auto __FAST_IO__ = []() noexcept {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  return 0;
}();
