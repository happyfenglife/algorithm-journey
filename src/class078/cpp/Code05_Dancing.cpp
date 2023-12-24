#include <iostream>

using namespace std;

const int MAXN = 6001;

int nums[MAXN];
bool boss[MAXN];

// 链式前向星建图
int head[MAXN];
int next_[MAXN];
int to[MAXN];
int cnt;

// no[i] : i为头的整棵树，在i不来的情况下，整棵树能得到的最大快乐值
int no[MAXN];
// yes[i] : i为头的整棵树，在i来的情况下，整棵树能得到的最大快乐值
int yes[MAXN];

void build(int n) {
  fill(begin(boss) + 1, begin(boss) + 1 + n, true);
  fill(begin(head) + 1, begin(head) + 1 + n, 0);
  cnt = 1;
}

void addEdge(int u, int v) {
  next_[cnt] = head[u];
  to[cnt] = v;
  head[u] = cnt++;
}

int n, h;

void f(int u) {
  no[u] = 0;
  yes[u] = nums[u];

  for (int ei = head[u], v; ei != 0; ei = next_[ei]) {
    v = to[ei];
    f(v);
    no[u] += max(no[v], yes[v]);
    yes[u] += no[v];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  build(n);
  for (int i = 1; i <= n; ++i) {
    cin >> nums[i];
  }

  for (int i = 1, low, high; i < n; ++i) {
    cin >> low >> high;
    addEdge(high, low);
    boss[low] = false;
  }

  for (int i = 1; i <= n; ++i) {
    if (boss[i]) {
      h = i;
      break;
    }
  }

  f(h);
  cout << max(no[h], yes[h]) << endl;
  return 0;
}
