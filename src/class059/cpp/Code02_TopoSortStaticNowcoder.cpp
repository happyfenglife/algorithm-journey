#include <iostream>
#include <cstring>

using namespace std;

// 拓扑排序模版（牛客）
// 链式前向星建图（静态方式）
// 测试链接 : https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c
const int MAXN = 200001;
const int MAXM = 200001;

// 建图相关，链式前向星
int head[MAXN];
int next_[MAXM];
int to_[MAXM];
int cnt;

// 拓扑排序，用到队列
int queue[MAXN];
int l, r;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

void build() {
  cnt = 1;
  memset(head, 0, size(head));
  memset(indegree, 0, sizeof(indegree));
}

// 用链式前向星建图
void addEdge(int f, int t) {
  next_[cnt] = head[f];
  to_[cnt] = t;
  head[f] = cnt++;
}

bool topoSort() {
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

    // 用链式前向星的方式，遍历cur的相邻节点
    for (int ei = head[cur]; ei != 0; ei = next_[ei]) {
      if (--indegree[to_[ei]] == 0) {
        queue[r++] = to_[ei];
      }
    }
  }

  return fill == n;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  while (cin >> n >> m) {
    build();

    for (int i = 0, from, to; i < m; ++i) {
      cin >> from >> to;
      addEdge(from, to);
      indegree[to]++;
    }

    if (!topoSort()) {
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
