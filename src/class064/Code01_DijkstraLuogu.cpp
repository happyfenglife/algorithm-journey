#include <iostream>
#include <cstring>

using namespace std;

// Dijkstra算法模版（洛谷）
// 静态空间实现 : 链式前向星 + 反向索引堆
// 测试链接 : https://www.luogu.com.cn/problem/P4779

const int MAXN = 100001;
const int MAXM = 200001;

// 链式前向星
int head[MAXN];
int next_[MAXM];
int to[MAXM];
int weight[MAXM];

int cnt;

// 反向索引堆
int heap[MAXN];

// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = i(>=0)，表示v这个节点，在堆上的i位置
int where[MAXN];
int heapSize;
int dist[MAXN];

int n, m, s;

void build() {
  cnt = 1;
  heapSize = 0;
  memset(head, 0, sizeof(head));
  memset(where, -1, sizeof(where));
  memset(dist, 0x3f, sizeof(dist));
}

// 链式前向星建图
void addEdge(int u, int v, int w) {
  next_[cnt] = head[u];
  to[cnt] = v;
  weight[cnt] = w;
  head[u] = cnt++;
}

void swap(int i, int j) {
  int tmp = heap[i];
  heap[i] = heap[j];
  heap[j] = tmp;
  where[heap[i]] = i;
  where[heap[j]] = j;
}

void heapInsert(int i) {
  while (dist[heap[i]] < dist[heap[(i - 1) / 2]]) {
    swap(i, (i - 1) / 2);
    i = (i - 1) / 2;
  }
}

void heapify(int i) {
  int l = 2 * i + 1;

  while (l < heapSize) {
    int best = (l + 1 < heapSize && dist[heap[l + 1]] < dist[heap[l]]) ? l + 1 : l;
    best = (dist[heap[best]] < dist[heap[i]]) ? best : i;

    if (i == best) {
      break;
    }

    swap(best, i);
    i = best;
    l = i * 2 + 1;
  }
}

int pop() {
  int ans = heap[0];
  swap(0, --heapSize);
  heapify(0);
  where[ans] = -2;
  return ans;
}

void addOrUpdateOrIgnore(int v, int w) {
  if (where[v] == -1) {
    heap[heapSize] = v;
    where[v] = heapSize++;
    dist[v] = w;
    heapInsert(where[v]);
  } else if (where[v] >= 0) {
    dist[v] = min(dist[v], w);
    heapInsert(where[v]);
  }
}

bool isEmpty() {
  return heapSize == 0;
}

void dijkstra() {
  addOrUpdateOrIgnore(s, 0);
  while (!isEmpty()) {
    int v = pop();

    for (int ei = head[v]; ei != 0; ei = next_[ei]) {
      addOrUpdateOrIgnore(to[ei], dist[v] + weight[ei]);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> m >> s) {
    build();

    for (int i = 0, u, v, w; i < m; ++i) {
      cin >> u >> v >> w;
      addEdge(u, v, w);
    }

    dijkstra();
    for (int i = 1; i < n; ++i) {
      cout << dist[i] << " ";
    }

    cout << dist[n] << "\n";
  }

  return EXIT_SUCCESS;
}
