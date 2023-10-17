#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 100001;
const int MAXM = 100001;

// 建图相关，链式前向星
int head[MAXN];
int next_[MAXM];
int to_[MAXM];

int cnt;

// 拓扑排序，不用队列，用小根堆，为了得到字典序最小的拓扑排序
priority_queue<int, vector<int>, greater<>> heap;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

// 清理之前的脏数据
void build() {
  cnt = 1;
  memset(head, 0, sizeof(head));
  memset(indegree, 0, sizeof(indegree));
}

// 用链式前向星建图
void addEdge(int f, int t) {
  next_[cnt] = head[f];
  to_[cnt] = t;
  head[f] = cnt++;
}

void topoSort() {
  for (int i = 1; i <= n; ++i) {
    if (indegree[i] == 0) {
      heap.push(i);
    }
  }

  int fill = 0;
  while (!heap.empty()) {
    int cur = heap.top();
    heap.pop();
    ans[fill++] = cur;

    // 用链式前向星的方式，遍历cur的相邻节点
    for (int ei = head[cur]; ei != 0; ei = next_[ei]) {
      if (--indegree[to_[ei]] == 0) {
        heap.push(to_[ei]);
      }
    }
  }
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

    topoSort();
    for (int i = 0; i < n - 1; ++i) {
      cout << ans[i] << " ";
    }

    cout << ans[n - 1] << endl;
  }

  return EXIT_SUCCESS;
}
