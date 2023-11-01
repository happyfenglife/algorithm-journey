#include <iostream>
#include <cstring>

using namespace std;

const int MAXN = 2001;
const int MAXM = 6001;

// SPFA需要
const int MAXQ = 4000001;

// 链式前向星建图需要
int head[MAXN];
int next_[MAXM];
int to[MAXM];

int weight[MAXM];
// 源点出发到每个节点的距离表
int dist[MAXN];

// 节点是否已经在队列中
bool visited[MAXN];

// 哪些节点被松弛了放入队列
int queue[MAXQ];

// 节点被松弛的次数
int updateCnt[MAXN];

int cnt;
int l, r;
int T, n, m;

void init() {
  cnt = 1;
  l = r = 0;
  memset(head, 0, sizeof(head));
  memset(visited, 0, sizeof(visited));
  memset(dist, 0x3f, sizeof(dist));
  memset(updateCnt, 0, sizeof(updateCnt));
}

void addEdge(int u, int v, int w) {
  next_[cnt] = head[u];
  to[cnt] = v;
  weight[cnt] = w;
  head[u] = cnt++;
}

// Bellman-Ford + SPFA优化的模版
bool SPFA() {
  dist[1] = 0;
  updateCnt[1]++;
  queue[r++] = 1;
  visited[1] = true;

  while (l < r) {
    int u = queue[l++];
    visited[u] = false;

    for (int ei = head[u], v, w; ei != 0; ei = next_[ei]) {
      v = to[ei];
      w = weight[ei];

      if (dist[u] + w < dist[v]) {
        dist[v] = w + dist[u];

        if (!visited[v]) {
          if (updateCnt[v]++ == n) {
            return true;
          }

          queue[r++] = v;
          visited[v] = true;
        }
      }
    }
  }

  return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> T;
  for (int j = 0; j < T; ++j) {
    cin >> n >> m;

    init();
    for (int i = 0, u, v, w; i < m; ++i) {
      cin >> u >> v >> w;

      addEdge(u, v, w);
      if (w >= 0) {
        addEdge(v, u, w);
      }
    }

    cout << (SPFA() ? "YES" : "NO") << endl;
  }

  return EXIT_SUCCESS;
}
