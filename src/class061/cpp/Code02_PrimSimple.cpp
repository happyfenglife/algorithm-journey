#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int MAXN = 5001;
const int MAXM = 400001;

// 链式前向星建图
int head[MAXN];
int next_[MAXM];
int to[MAXM];
int weight[MAXM];

bool visited[MAXN];

int cnt, nodeCnt, ans;
int n, m;

struct edge {
  int v;
  int w;
};

struct comp {
  bool operator()(edge &e1, edge &e2) {
    return e1.w > e2.w;
  }
};

void addEdge(int u, int v, int w) {
  next_[cnt] = head[u];
  to[cnt] = v;
  weight[cnt] = w;
  head[u] = cnt++;
}

void build() {
  cnt = 1;
  nodeCnt = 1;
  ans = 0;
  memset(head, 0, sizeof(head));
  memset(visited, 0, sizeof(visited));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> m) {
    build();

    for (int i = 1, u, v, w; i <= m; ++i) {
      cin >> u >> v >> w;
      addEdge(u, v, w);
      addEdge(v, u, w);
    }

    priority_queue<edge, vector<edge>, comp> heap;
    for (int ei = head[1]; ei != 0; ei = next_[ei]) {
      heap.push({to[ei], weight[ei]});
    }

    visited[1] = true;

    while (!heap.empty()) {
      edge e = heap.top();
      heap.pop();

      int v = e.v, w = e.w;
      if (!visited[v]) {
        nodeCnt++;
        visited[v] = true;
        ans += w;

        for (int ei = head[v]; ei != 0; ei = next_[ei]) {
          heap.push({to[ei], weight[ei]});
        }
      }
    }

    if (nodeCnt == n) {
      cout << ans << endl;
    } else {
      cout << "orz" << endl;
    }
  }

  return 0;
}
