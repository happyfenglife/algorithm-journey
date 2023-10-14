#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// 点的最大数量
const int MAXN = 11;

// 边的最大数量
// 只有链式前向星方式建图需要这个数量
// 注意如果无向图的最大数量是m条边，数量要准备m*2
// 因为一条无向边要加两条有向边
const int MAXM = 21;

// 邻接矩阵方式建图
int graph1[MAXN][MAXN];

// 邻接表方式建图
vector<vector<pair<int, int>>> graph2;

// 链式前向星方式建图
int head[MAXN];
int next_[MAXM];
int to[MAXM];

// 如果有权重，那么需要这个数组
int weight[MAXM];
int cnt;

void build(int n) {
  memset(graph1, 0, sizeof(graph1));

  graph2.clear();
  graph2.resize(n + 1);

  cnt = 1;
  memset(head, 0, sizeof(head));
}

// 链式前向星加边
void addEdge(int u, int v, int w) {
  next_[cnt] = head[u];
  to[cnt] = v;
  weight[cnt] = w;
  head[u] = cnt++;
}

// 三种方式建立有向带权图
void directGraph(vector<vector<int>> &edges) {
  // 邻接矩阵建图
  for (auto &edge : edges) {
    graph1[edge[0]][edge[1]] = edge[2];
  }

  // 邻接表建图
  for (auto &edge : edges) {
    graph2[edge[0]].emplace_back(edge[1], edge[2]);
  }

  // 链式前向星建图
  for (auto &edge : edges) {
    addEdge(edge[0], edge[1], edge[2]);
  }
}

void traversal(int n) {
  cout << "邻接矩阵遍历 :\n";
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      cout << graph1[i][j] << " ";
    }

    cout << "\n";
  }

  cout << "邻接表遍历 :\n";
  for (int i = 1; i <= n; ++i) {
    cout << i << "(邻居、边权) : ";

    for (auto &edge : graph2[i]) {
      cout << "(" << edge.first << ", " << edge.second << ") ";
    }

    cout << "\n";
  }

  cout << "链式前向星遍历 :\n";
  for (int i = 1; i <= n; ++i) {
    cout << i << "(邻居、边权) : ";

    for (int ei = head[i]; ei != 0; ei = next_[ei]) {
      cout << "(" << to[ei] << ", " << weight[ei] << ") ";
    }

    cout << "\n";
  }
}

// 三种方式建立无向带权图
void undirectGraph(vector<vector<int>> &edges) {
  // 邻接矩阵建图
  for (auto &edge : edges) {
    graph1[edge[0]][edge[1]] = edge[2];
    graph1[edge[1]][edge[0]] = edge[2];
  }

  // 邻接表建图
  for (auto &edge : edges) {
    graph2[edge[0]].emplace_back(edge[1], edge[2]);
    graph2[edge[1]].emplace_back(edge[0], edge[2]);
  }

  // 链式前向星建图
  for (auto &edge : edges) {
    addEdge(edge[0], edge[1], edge[2]);
    addEdge(edge[1], edge[0], edge[2]);
  }
}

int main() {
  int n1 = 4;
  vector<vector<int>> edges1 = {{1, 3, 6}, {4, 3, 4}, {2, 4, 2}, {1, 2, 7}, {2, 3, 5}, {3, 1, 1}};
  build(n1);
  directGraph(edges1);
  traversal(n1);
  cout << "==============================" << endl;

  int n2 = 5;
  vector<vector<int>> edges2 = {{3, 5, 4}, {4, 1, 1}, {3, 4, 2}, {5, 2, 4}, {2, 3, 7}, {1, 5, 5}, {4, 2, 6}};
  build(n2);
  undirectGraph(edges2);
  traversal(n2);

  return EXIT_SUCCESS;
}
