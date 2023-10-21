#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

// 飞行路线（语言提供的堆）
// Alice和Bob现在要乘飞机旅行，他们选择了一家相对便宜的航空公司
// 该航空公司一共在n个城市设有业务，设这些城市分别标记为0 ~ n−1
// 一共有m种航线，每种航线连接两个城市，并且航线有一定的价格
// Alice 和 Bob 现在要从一个城市沿着航线到达另一个城市，途中可以进行转机
// 航空公司对他们这次旅行也推出优惠，他们可以免费在最多k种航线上搭乘飞机
// 那么 Alice 和 Bob 这次出行最少花费多少
// 测试链接 : https://www.luogu.com.cn/problem/P4568
const int MAXN = 10001;
const int MAXM = 100001;
const int MAXK = 11;

// 链式前向星建图需要
int head[MAXN];
int next_[MAXM];
int to[MAXM];
int weight[MAXM];

int cnt;

// Dijkstra需要
int dist[MAXN][MAXK];
bool visited[MAXN][MAXK];

int n, m, k, s, t;

struct route {
  int v;
  int w;
  int k;

  route(int _v, int _w, int _k)
      : v(_v), w(_w), k(_k) {}
};

struct comp {
  bool operator()(route &r1, route &r2) {
    return r1.w > r2.w;
  }
};

priority_queue<route, vector<route>, comp> heap;

void build() {
  cnt = 1;
  memset(head, 0, sizeof(head));
  memset(dist, 0x3f, sizeof(dist));
  memset(visited, 0, sizeof(visited));

  while (!heap.empty()) {
    heap.pop();
  }
}

void addEdge(int u, int v, int w) {
  next_[cnt] = head[u];
  to[cnt] = v;
  weight[cnt] = w;
  head[u] = cnt++;
}

int dijkstra() {
  dist[s][0] = 0;
  heap.emplace(s, 0, 0);
  while (!heap.empty()) {
    auto [u, cost, use] = heap.top();
    heap.pop();
    if (visited[u][use]) {
      continue;
    }

    visited[u][use] = true;
    if (u == t) {
      // 常见剪枝
      // 发现终点直接返回
      // 不用等都结束
      return cost;
    }

    for (int ei = head[u], v, w; ei != 0; ei = next_[ei]) {
      v = to[ei];
      w = weight[ei];

      if (use < k && dist[v][use + 1] > dist[u][use]) {
        dist[v][use + 1] = dist[u][use];
        heap.emplace(v, dist[v][use + 1], use + 1);
      }

      if (dist[v][use] > dist[u][use] + w) {
        dist[v][use] = dist[u][use] + w;
        heap.emplace(v, dist[v][use], use);
      }
    }
  }

  return -1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> m >> k) {
    cin >> s >> t;

    build();
    for (int i = 0, u, v, w; i < m; ++i) {
      cin >> u >> v >> w;
      addEdge(u, v, w);
      addEdge(v, u, w);
    }

    cout << dijkstra() << "\n";
  }

  return 0;
}
