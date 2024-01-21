#include <bits/stdc++.h>

using namespace std;

// 判断较小的数字是否是质数
// 时间复杂度O(根号n)
bool isPrime(long long n)
{
  if (n <= 1)
  {
    return false;
  }

  // 2 ... 根号n
  for (long long i = 2; i * i <= n; ++i)
  {
    if (!(n % i))
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[])
{
  cout << isPrime(4) << endl;

  return 0;
}
