#include <iostream>

using namespace std;

// Floyd算法模版（洛谷）
// 测试链接 : https://www.luogu.com.cn/problem/P2910
const int MAXN = 101;
const int MAXM = 10001;
int dist[MAXN][MAXM];
int path[MAXM];
int n, m, ans;

void floyd() {
  // O(N^3)的过程
  // 枚举每个跳板
  // 注意，跳板要最先枚举！跳板要最先枚举！跳板要最先枚举！
  for (int k = 1; k <= n; ++k) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        // i -> .....k .... -> j
        // distance[i][j]能不能缩短
        // distance[i][j] = min ( distance[i][j] , distance[i][k] + distance[k][j])
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> m) {
    for (int i = 1; i <= m; ++i) {
      cin >> path[i];
    }

    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cin >> dist[i][j];
      }
    }

    floyd();
    ans = 0;
    for (int i = 2; i <= m; ++i) {
      ans += dist[path[i - 1]][path[i]];
    }

    cout << ans << endl;
  }

  return 0;
}
