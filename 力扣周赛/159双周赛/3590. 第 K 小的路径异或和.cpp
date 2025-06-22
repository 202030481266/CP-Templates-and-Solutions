#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;
static constexpr int maxn = 5e4 + 7;
static constexpr int maxv = 2e5 + 7;
static constexpr int N = maxn * 200;

int n, m, tot; // m is the max value, n is the max index
int ls[N], rs[N], sum[N], root[maxv<<2];
int val[maxn], dfn[maxn], rdfn[maxn], siz[maxn], dfnCnt = 0;

// 线段树套线段树

int innerUpdate(int rt, int l, int r, int p, int v) {
    if (!rt) {
        rt = ++tot;
        ls[rt] = rs[rt] = sum[rt] = 0;
    }
    if (l == r) {
        sum[rt] += v;
        return rt;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[rt] = innerUpdate(ls[rt], l, mid, p, v);
    else rs[rt] = innerUpdate(rs[rt], mid + 1, r, p, v);
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    return rt;
}

int innerQuery(int rt, int l, int r, int x) {
    if (!rt) return 0;
    if (l == r) return sum[rt];
    int mid = (l + r) >> 1;
    if (x <= mid) return sum[rs[rt]] + innerQuery(ls[rt], l, mid, x);
    else return innerQuery(rs[rt], mid + 1, r, x);
}

void build(int rt, int l, int r) {
    root[rt] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
}

void update(int rt, int l, int r, int p, int idx, int v) {
    root[rt] = innerUpdate(root[rt], 1, n, idx, v);
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (p <= mid) update(rt << 1, l, mid, p, idx, v);
    else update(rt << 1 | 1, mid + 1, r, p, idx, v);
}

int query(int rt, int l, int r, int x, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int left_sz = innerQuery(root[rt << 1], 1, n, x);
    if (left_sz >= k) return query(rt << 1, l, mid, x, k);
    else return query(rt << 1 | 1, mid + 1, r, x, k - left_sz);
}

int pos[maxv];

class Solution {
public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        n = par.size();
        vector g(n, vector<int>());
        for (int i = 1; i < n; ++i) {
            g[par[i]].push_back(i);
        }
        dfnCnt = 0;
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            val[u] = val[fa] ^ vals[u];
            dfn[u] = ++dfnCnt;
            rdfn[dfnCnt] = u;
            siz[u] = 1;
            for (int v : g[u]) {
                self(self, v, u);
                siz[u] += siz[v];
            }
        };
        val[0] = 0;
        dfs(dfs, 0, 0);
        m = 0;
        for (int i = 0; i < n; ++i) {
            pos[val[i]] = 0;
            m = max(m, val[i]);
        }
        tot = 0;
        build(1, 0, m);
        vector<array<int, 4>> qs(queries.size());
        vector<int> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int x = queries[i][0], k = queries[i][1];
            // [l, r, k, idx]
            qs[i][0] = dfn[x];
            qs[i][1] = dfn[x] + siz[x] - 1;
            qs[i][2] = k;
            qs[i][3] = i;
        }
        sort(qs.begin(), qs.end(), [&](const auto& x, const auto& y) {
            return x[1] < y[1];
        });
        int p = 0;
        for (int i = 1; i <= n && p < queries.size(); ++i) {
            int v = val[rdfn[i]];
            if (pos[v]) update(1, 0, m, v, pos[v], -1);
            update(1, 0, m, v, i, 1);
            pos[v] = i;
            while (p < queries.size() && qs[p][1] == i) {
                if (innerQuery(root[1], 1, n, qs[p][0]) < qs[p][2]) ans[qs[p][3]] = -1;
                else ans[qs[p][3]] = query(1, 0, m, qs[p][0], qs[p][2]);
                ++p;
            }
        }
        return ans;
    }
};

// 莫队 + 树状数组
#include <bits/stdc++.h>
using namespace std;

static constexpr int maxn = 5e4 + 7;
static constexpr int maxv = 2e5 + 7;

struct Fenwick {
    int n;
    vector<int> t;

    explicit Fenwick(int _n): n(_n), t(n+1, 0) {}

    static inline int lowbit(int x) {
        return x & -x;
    }

    void init(int N) {
        n = N;
        for (int i = 1; i <= n; i++) {
            t[i] = 0;
        }
    }

    void add(int i, int v) {
        for (; i <= n; i += lowbit(i)) {
            t[i] += v;
        }
    }

    int sum(int i) const {
        int s = 0;
        for (; i > 0; i -= lowbit(i)) {
            s += t[i];
        }
        return s;
    }

    int find_by_prefix(int S) const {
        int pos = 0;
        int acc = 0;
        int mask = 1;
        while ((mask << 1) <= n) mask <<= 1;
        for (int k = mask; k > 0; k >>= 1) {
            if (pos + k <= n && acc + t[pos + k] < S) {
                acc += t[pos + k];
                pos += k;
            }
        }
        return pos + 1;
    }
};

int cnt[maxv];
Fenwick tree(maxv);

void add(int value) {
    ++value; // 保证非0
    cnt[value]++;
    if (cnt[value] == 1) tree.add(value, 1);
}

void del(int value) {
    ++value; // 保证非0
    cnt[value]--;
    if (cnt[value] == 0) tree.add(value, -1);
}

class Solution {
public:
    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        int n = par.size();
        vector g(n, vector<int>());
        vector<int> dfn(n), rdfn(n+1), siz(n), val(n);
        for (int i = 1; i < n; ++i) {
            g[par[i]].push_back(i);
        }
        int dfnCnt = 0;
        auto dfs = [&](auto&& self, int u, int fa) -> void {
            val[u] = val[fa] ^ vals[u];
            dfn[u] = ++dfnCnt;
            rdfn[dfnCnt] = u;
            siz[u] = 1;
            for (int v : g[u]) {
                self(self, v, u);
                siz[u] += siz[v];
            }
        };
        dfs(dfs, 0, 0);
        int block_size = sqrt(n);
        vector<array<int, 4>> qs(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            int x = queries[i][0], k = queries[i][1];
            qs[i][0] = dfn[x];
            qs[i][1] = dfn[x] + siz[x] - 1;
            qs[i][2] = k;
            qs[i][3] = i;
        }
        vector<int> ans(queries.size());
        ranges::sort(qs, [&](const auto& x, const auto& y) {
            int block1 = x[0] / block_size, block2 = y[0] / block_size;
            if (block1 != block2) {
                return block1 < block2;
            }
            if (block1 % 2 == 0) {
                return x[1] < y[1];
            }
            return x[1] > y[1];
        });
        int l = 1, r = 0, mx = *ranges::max_element(val);
        tree.init(mx + 7);
        for (int i = 0; i < n; ++i) cnt[val[i] + 1] = 0;
        for (auto& q : qs) {
            while (l > q[0]) add(val[rdfn[--l]]);
            while (r < q[1]) add(val[rdfn[++r]]);
            while (l < q[0]) del(val[rdfn[l++]]);
            while (r > q[1]) del(val[rdfn[r--]]);
            int res = tree.find_by_prefix(q[2]);
            if (res > mx + 1) ans[q[3]] = -1;
            else ans[q[3]] = res - 1;
        }
        return ans;
    }
};