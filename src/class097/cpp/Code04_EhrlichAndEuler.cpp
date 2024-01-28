#include <bits/stdc++.h>

using namespace std;

// 计数质数
// 给定整数n，返回小于非负整数n的质数的数量
// 测试链接 : https://leetcode.cn/problems/count-primes/
class Solution
{
  public:
    int countPrimes(int n)
    {
      return ehrlich(n - 1);
    }

  private:
    // 埃氏筛统计0 ~ n范围内的质数个数
    // 时间复杂度O(n * log(logn))
    // 对埃氏筛的改进(只是计数)
    int ehrlich(int n)
    {
      if (n <= 1)
      {
        return 0;
      }

      // visit[i] = true，代表i是合数
      // visit[i] = false，代表i是质数
      // 初始时认为0~n所有数都是质数
      vector<bool> visit(n + 1);

      // 先把所有的偶数去掉，但是算上2
      // 估计的质数数量，如果发现更多合数，那么cnt--
      int cnt = (n + 1) / 2;
      for (int i = 3; i * i <= n; i += 2)
      {
        if (!visit[i])
        {
          for (int j = i * i; j <= n; j += 2 * i)
          {
            if (!visit[j])
            {
              visit[j] = true;
              --cnt;
            }
          }
        }
      }

      return cnt;
    }

    // 欧拉筛统计0 ~ n范围内的质数个数
    // 时间复杂度O(n)
    int euler(int n)
    {
      vector<bool> visit(n + 1);
      vector<int> prime(n / 2 + 1);
      int cnt{};

      for (int i = 2; i <= n; ++i)
      {
        if (!visit[i])
        {
          prime[cnt++] = i;
        }

        for (int j = 0; j < cnt; ++j)
        {
          if (i * prime[j] > n)
          {
            break;
          }

          visit[i * prime[j]] = true;
          if (!(i % prime[j]))
          {
            break;
          }
        }
      }

      return cnt;
    }
};
