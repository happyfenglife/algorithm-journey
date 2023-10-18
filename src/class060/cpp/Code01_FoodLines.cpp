#include <iostream>
#include <cstring>

using namespace std;

// 最大食物链计数
// a -> b，代表a在食物链中被b捕食
// 给定一个有向无环图，返回
// 这个图中从最初级动物到最顶级捕食者的食物链有几条
// 测试链接 : https://www.luogu.com.cn/problem/P4017

const int MAXN = 5001;
const int MAXM = 500001;
const int MOD = 80112002;

// 链式前向星建图
int head[MAXN];
int next_[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序需要的队列
int queue[MAXN];

// 拓扑排序需要的入度表
int indegree[MAXN];

// 拓扑排序需要的推送信息
int lines[MAXN];

int n, m;

void build() {
  cnt = 1;
  memset(indegree, 0, sizeof(indegree));
  memset(lines, 0, sizeof(lines));
  memset(head, 0, sizeof(head));
}

void addEdge(int u, int v) {
  next_[cnt] = head[u];
  to[cnt] = v;
  head[u] = cnt++;
}

int topoSort() {
  int l = 0, r = 0;
  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) {
      queue[r++] = i;
      lines[i] = 1;
    }
  }

  int ans = 0;
  while (l < r) {
    int u = queue[l++];

    if (head[u] == 0) {
      ans = (ans + lines[u]) % MOD;
    } else {
      for (int ei = head[u], v; ei != 0; ei = next_[ei]) {
        // u -> v
        v = to[ei];
        lines[v] = (lines[v] + lines[u]) % MOD;

        if (--indegree[v] == 0) {
          queue[r++] = v;
        }
      }
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> m) {
    build();

    for (int i = 0, u, v; i < m; ++i) {
      cin >> u >> v;
      addEdge(u, v);
      indegree[v]++;
    }

    int ans = topoSort();
    cout << ans << "\n";
  }

  return EXIT_SUCCESS;
}