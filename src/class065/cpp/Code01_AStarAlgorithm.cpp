#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>

using namespace std;

const int n = 4000;
const int m = 4000;

int dir[] = {-1, 0, 1, 0, -1};
int grid[n][m];
int srcX, srcY;
int destX, destY;

int dist[n][m];
bool visited[n][m];

void init() {
  memset(dist, 0x3f, sizeof(dist));
  memset(visited, 0, sizeof(visited));

  dist[srcX][srcY] = 1;
}

void initGrid() {
  for (auto &i : grid) {
    for (int &j : i) {
      if (rand() % 100 < 30) {
        // 每个格子有30%概率是0
        j = 0;
      } else {
        // 每个格子有70%概率是1
        j = 1;
      }
    }
  }
}

// 曼哈顿距离
int manhattanDist(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

// 对角线距离
int diagonalDist(int x1, int y1, int x2, int y2) {
  return max(abs(x2 - x1), abs(y2 - y1));
}

// 欧式距离
int euroDist(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离

// Dijkstra算法
int dijkstra() {
  init();

  auto comp = [](vector<int> &v1, vector<int> &v2) noexcept {
    return v1[2] > v2[2];
  };
  priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> heap(comp);
  heap.push({srcX, srcY, 1});

  while (!heap.empty()) {
    vector<int> cur = heap.top();
    heap.pop();

    int x = cur[0], y = cur[1];
    if (visited[x][y]) {
      continue;
    }

    visited[x][y] = true;
    if (x == destX && y == destY) {
      return dist[x][y];
    }

    for (int i = 0, nx, ny; i < 4; ++i) {
      nx = x + dir[i];
      ny = y + dir[i + 1];

      if (nx >= 0 && nx < n
          && ny >= 0 && ny < m
          && grid[nx][ny] == 1
          && !visited[nx][ny]
          && dist[x][y] + 1 < dist[nx][ny]) {
        dist[nx][ny] = dist[x][y] + 1;
        heap.push({nx, ny, dist[nx][ny]});
      }
    }
  }

  return -1;
}

// A*算法
int AStar() {
  init();

  auto comp = [](vector<int> &v1, vector<int> &v2) noexcept {
    return v1[2] > v2[2];
  };
  priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> heap(comp);
  heap.push({srcX, srcY, 1});

  while (!heap.empty()) {
    vector<int> cur = heap.top();
    heap.pop();

    int x = cur[0], y = cur[1];
    if (visited[x][y]) {
      continue;
    }

    visited[x][y] = true;
    if (x == destX && y == destY) {
      return dist[x][y];
    }

    for (int i = 0, nx, ny; i < 4; ++i) {
      nx = x + dir[i];
      ny = y + dir[i + 1];

      if (nx >= 0 && nx < n
          && ny >= 0 && ny < m
          && grid[nx][ny] == 1
          && !visited[nx][ny]
          && dist[x][y] + 1 < dist[nx][ny]) {
        dist[nx][ny] = dist[x][y] + 1;
        heap.push({nx, ny, dist[nx][ny] + manhattanDist(nx, ny, destX, destY)});
      }
    }
  }

  return -1;
}

// 为了测试
int main() {
  int testTime = 100000;
  cout << "test begin..." << endl;

  for (int i = 0; i < testTime; i++) {
    initGrid();

    srcX = rand() % n;
    srcY = rand() % n;
    destX = rand() % n;
    destY = rand() % n;

    int ans1 = dijkstra();
    int ans2 = AStar();

    if (ans1 != ans2) {
      cout << "Oops!" << endl;
    }
  }

  cout << "test end..." << endl;
  return 0;
}
