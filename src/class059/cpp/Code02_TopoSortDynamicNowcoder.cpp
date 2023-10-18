#include <iostream>
#include <vector>

using namespace std;

// 拓扑排序模版（牛客）
// 邻接表建图（动态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c

const int MAXN = 200001;

// 拓扑排序，用到队列
int queue[MAXN];
int l, r;

// 入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

// 有拓扑排序返回true
// 没有拓扑排序返回false
bool topoSort(vector<vector<int>> &graph) {
  l = r = 0;
  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) {
      queue[r++] = i;
    }
  }

  int fill = 0;
  while (l < r) {
    int cur = queue[l++];
    ans[fill++] = cur;

    for (int next : graph[cur]) {
      if (--indegree[next] == 0) {
        queue[r++] = next;
      }
    }
  }

  return fill == n;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n >> m) {
    vector<vector<int>> graph(n + 1);

    for (int i = 0, from, to; i < m; ++i) {
      cin >> from >> to;
      graph[from].push_back(to);
      indegree[to]++;
    }

    if (!topoSort(graph)) {
      cout << -1 << endl;
    } else {
      for (int i = 0; i < n - 1; ++i) {
        cout << ans[i] << " ";
      }

      cout << ans[n - 1] << endl;
    }
  }

  return EXIT_SUCCESS;
}
