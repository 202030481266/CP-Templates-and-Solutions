#include <vector>
#include <iostream>

using namespace std;

// Fenwick Tree 模板
template <typename T>
class Fenwick {
 public:
  vector<T> fenw;
  int n;

  explicit Fenwick(int n) : n(n) {
    fenw.resize(n);
  }

  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }

  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};

// 一维树状数组
class TreeArray {
 public:
  int size = 0;
  vector<int> tree;

  TreeArray() {}

  void init(int n) {
    size = n;
    tree = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      int temp;
      cin >> temp;
      add(i, temp);
    }
  }

  int lowbit(int x) {
    return x & (-x);
  }

  void add(int x, int value) {
    for (int i = x; i <= size; i += lowbit(i)) {
      tree[i] += value;
    }
  }

  int get_sum(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i)) {
      sum += tree[i];
    }
    return sum;
  }

  int get_sum(int x, int y) {
    return get_sum(y) - get_sum(x - 1);
  }
};

// 差分树状数组 (区间修改和单点查询)
class BitSingle {
 public:
  int size = 0;
  vector<int> tree;

  BitSingle() {}

  void init(int n) {
    size = n;
    tree = vector<int>(n + 1, 0);
    int first;
    cin >> first;
    add(1, first);
    for (int i = 2; i <= n; i++) {
      int temp;
      cin >> temp;
      add(i, temp - first);
      first = temp;
    }
  }

  int lowbit(int x) {
    return x & (-x);
  }

  void add(int x, int value) {
    for (int i = x; i <= size; i += lowbit(i)) {
      tree[i] += value;
    }
  }

  void add(int x, int y, int value) {
    add(x, value);
    add(y + 1, -value);
  }

  int get_sum(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i)) {
      sum += tree[i];
    }
    return sum;
  }
};

// 区间修改和区间查询
class BitRange {
 public:
  int size = 0;
  vector<int> tree1, tree2;

  BitRange() {}

  void init(int n) {
    size = n;
    tree1 = vector<int>(n + 1, 0);
    tree2 = vector<int>(n + 1, 0);
    int first;
    cin >> first;
    add(1, first);
    for (int i = 2; i <= n; i++) {
      int temp;
      cin >> temp;
      add(i, temp - first);
      first = temp;
    }
  }

  int lowbit(int x) {
    return x & (-x);
  }

  void add(int x, int value) {
    for (int i = x; i <= size; i += lowbit(i)) {
      tree1[i] += value;
      tree2[i] += (value * x);
    }
  }

  void add(int x, int y, int value) {
    add(x, value);
    add(y + 1, -value);
  }

  int get_sum(int x) {
    int sum = 0;
    for (int i = x; i; i -= lowbit(i)) {
      sum += ((x + 1) * tree1[i] - tree2[i]);
    }
    return sum;
  }

  int get_sum(int x, int y) {
    return get_sum(y) - get_sum(x - 1);
  }
};

// 普通树状数组
class SimpleFenwick {
 public:
  using ll = long long;
  ll n;
  vector<ll> c;

  explicit SimpleFenwick(ll size) : n(size), c(size + 1, 0) {}

  ll lowbit(ll x) {
    return x & (-x);
  }

  ll sum(ll x) {
    ll res = 0;
    while (x > 0) {
      res += c[x];
      x -= lowbit(x);
    }
    return res;
  }

  void update(ll x, ll w) {
    while (x <= n) {
      c[x] += w;
      x += lowbit(x);
    }
  }

  ll get(ll x) {
    ll res = c[x];
    for (int i = 1; i < (x & (-x)); i <<= 1) {
      res -= c[x - i];
    }
    return res;
  }

  ll get_kth(ll k) {
    ll ans = 0, cnt = 0;
    for (int i = 20; i >= 0; i--) {
      ans += 1 << i;
      if (ans >= n || cnt + c[ans] >= k) {
        ans -= 1 << i;
      } else {
        cnt += c[ans];
      }
    }
    return ans + 1;
  }
};

// 二维树状数组
class Fenwick2D {
 public:
  static const int kMaxN = 1000;  // 请根据需要调整
  int n;
  vector<vector<int>> c;

  explicit Fenwick2D(int size) : n(size), c(n + 1, vector<int>(n + 1, 0)) {}

  int lowbit(int x) {
    return x & (-x);
  }

  void update(int x, int y, int d) {
    for (int i = x; i <= n; i += lowbit(i)) {
      for (int j = y; j <= n; j += lowbit(j)) {
        c[i][j] += d;
      }
    }
  }

  int ask(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
      for (int j = y; j > 0; j -= lowbit(j)) {
        res += c[i][j];
      }
    }
    return res;
  }
};

// 支持最值和单点修改的树状数组
class MaxFenwick {
 public:
  static const int kMaxN = 100000;  // 请根据需要调整
  ll n;
  vector<ll> c;
  vector<ll> a;

  explicit MaxFenwick(ll size) : n(size), c(size + 1, 0), a(size + 1, 0) {}

  int lowbit(int x) {
    return x & (-x);
  }

  void init() {
    for (int i = 1; i <= n; i++) {
      c[i] = a[i];
      for (int j = 1; j < lowbit(i); j <<= 1) {
        c[i] = max(c[i], c[i - j]);
      }
    }
  }

  ll query(ll l, ll r) {
    ll ans = a[r];
    while (l <= r) {
      if (r - lowbit(r) >= l - 1) {
        ans = max(ans, c[r]);
        r -= lowbit(r);
      } else {
        ans = max(ans, a[r--]);
      }
    }
    return ans;
  }

  void update(int x, int d) {
    a[x] = d;
    for (int i = x; i <= n; i += lowbit(i)) {
      if (d >= c[i]) {
        c[i] = d;
        continue;
      }
      c[i] = a[i];
      for (int j = 1; j < lowbit(i); j <<= 1) {
        c[i] = max(c[i], c[i - j]);
      }
    }
  }
};

// 二维差分树状数组相关函数（独立实现）
class Fenwick2DDiff {
 public:
  static const int kMaxN = 1000;  // 请根据需要调整
  ll n, m;
  vector<vector<ll>> c[4];

  Fenwick2DDiff(ll rows, ll cols) : n(rows), m(cols) {
    for (int i = 0; i < 4; i++) {
      c[i] = vector<vector<ll>>(n + 1, vector<ll>(m + 1, 0));
    }
  }

  void update_point(int id, int x, int y, int d) {
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        c[id][i][j] += d;
      }
    }
  }

  ll sum(int id, int x, int y) {
    ll res = 0;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        res += c[id][i][j];
      }
    }
    return res;
  }

  void update(int x1, int y1, int x2, int y2, int d) {
    update_point(0, x1, y1, d);
    update_point(0, x1, y2 + 1, -d);
    update_point(0, x2 + 1, y1, -d);
    update_point(0, x2 + 1, y2 + 1, d);
    update_point(1, x1, y1, x1 * d);
    update_point(1, x1, y2 + 1, -x1 * d);
    update_point(1, x2 + 1, y1, -(x2 + 1) * d);
    update_point(1, x2 + 1, y2 + 1, (x2 + 1) * d);
    update_point(2, x1, y1, y1 * d);
    update_point(2, x1, y2 + 1, -(y2 + 1) * d);
    update_point(2, x2 + 1, y1, -y1 * d);
    update_point(2, x2 + 1, y2 + 1, (y2 + 1) * d);
    update_point(3, x1, y1, x1 * y1 * d);
    update_point(3, x1, y2 + 1, -x1 * (y2 + 1) * d);
    update_point(3, x2 + 1, y1, -(x2 + 1) * y1 * d);
    update_point(3, x2 + 1, y2 + 1, (x2 + 1) * (y2 + 1) * d);
  }

  ll get(int x, int y) {
    return (x + 1) * (y + 1) * sum(0, x, y) - (y + 1) * sum(1, x, y) -
           (x + 1) * sum(2, x, y) + sum(3, x, y);
  }

  ll solve(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
  }
};