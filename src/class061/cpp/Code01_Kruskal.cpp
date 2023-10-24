#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

const int MAXN = 5001;
const int MAXM = 200001;

struct edge {
  int u, v, w;
} edges[MAXM];

bool comp(edge &e1, edge &e2) {
  return e1.w < e2.w;
}

int n, m;

int father[MAXN];

void build() {
  iota(father + 1, father + n + 1, 1);
}

int find(int i) {
  if (i != father[i]) {
    father[i] = find(father[i]);
  }

  return father[i];
}

bool conn(int u, int v) {
  int fu = find(u);
  int fv = find(v);

  if (fu != fv) {
    father[fu] = fv;
    return true;
  } else {
    return false;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  while (cin >> n >> m) {
    build();

    for (int i = 0; i < m; ++i) {
      cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(edges, edges + m, comp);
    int ans = 0, cnt = 0;
    for (int i = 0; i < m; ++i) {
      if (conn(edges[i].u, edges[i].v)) {
        cnt++;
        ans += edges[i].w;
      }
    }

    if (cnt == n - 1) {
      cout << ans << endl;
    } else {
      cout << "orz\n";
    }
  }

  return 0;
}
