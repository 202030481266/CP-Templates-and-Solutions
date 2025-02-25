// https://www.luogu.com.cn/problem/P4175
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 8e4 + 7;
const int N = maxn * 200;
int n, m, root[maxn], dfn[maxn], ids[maxn], tot, cnt;
int ls[N], rs[N], sum[N], arr[maxn], ops[maxn][3];
int a[maxn<<1], len, f[maxn][20], dep[maxn], siz[maxn];
int addgroup[maxn], subgroup[maxn], add_len = 0, sub_len = 0;
vector<int> g[maxn];

// dfn序号 + LCA相关
void dfs(int u, int fa) {
    dfn[u] = ++cnt;
    ids[cnt] = u;
    dep[u] = dep[fa] + 1;
    f[u][0] = fa;
    siz[u] = 1;
    for (int i = 1; i < 20; ++i) f[u][i] = f[f[u][i-1]][i-1];
    for (int v : g[u]) {
        if (v != fa) {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}
int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
// 线段树相关
int update(int rt, int l, int r, int p, int v) {
    if (!rt) rt = ++tot;
    if (l == r) {
        sum[rt] += v;
        return rt;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) ls[rt] = update(ls[rt], l, mid, p, v);
    else rs[rt] = update(rs[rt], mid+1, r, p, v);
    sum[rt] = sum[ls[rt]] + sum[rs[rt]];
    return rt;
}
int query(int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int right_sum = 0;
    for (int i = 1; i <= add_len; ++i) right_sum += sum[rs[addgroup[i]]];
    for (int i = 1; i <= sub_len; ++i) right_sum -= sum[rs[subgroup[i]]];
    if (right_sum >= k) {
        for (int i = 1; i <= add_len; ++i) addgroup[i] = rs[addgroup[i]];
        for (int i = 1; i <= sub_len; ++i) subgroup[i] = rs[subgroup[i]];
        return query(mid+1, r, k);
    }
    else {
        for (int i = 1; i <= add_len; ++i) addgroup[i] = ls[addgroup[i]];
        for (int i = 1; i <= sub_len; ++i) subgroup[i] = ls[subgroup[i]];
        return query(l, mid, k - right_sum);
    }
}
// 树状数组逻辑，这里针对的是dfn序号的树状数组
// 区间更新 + 单点查询
int lowbit(int x) { return x & -x;}
int get(int x) {
    return lower_bound(a + 1, a + 1 + len, x) - a;
}
void add(int pos, int val, int change) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        root[i] = update(root[i], 1, len, val, change);
    }
}
int solve(int u, int v, int k) {
    // [u,v] 路径上的k大值
    add_len = sub_len = 0;
    int l_uv = lca(u, v), f_l = f[l_uv][0];
    int tot_node = dep[u] + dep[v] - 2 * dep[l_uv] + 1;
    if (tot_node < k) return -1;
    for (int i = dfn[u]; i; i -= lowbit(i)) addgroup[++add_len] = root[i];
    for (int i = dfn[v]; i; i -= lowbit(i)) addgroup[++add_len] = root[i];
    for (int i = dfn[l_uv]; i; i -= lowbit(i)) subgroup[++sub_len] = root[i];
    for (int i = dfn[f_l]; i; i -= lowbit(i)) subgroup[++sub_len] = root[i];
    return query(1, len, k);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        a[++len] = arr[i];
    }
    for (int u, v, i = 1; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }    
    for (int i = 1; i <= m; ++i) {
        cin >> ops[i][0] >> ops[i][1] >> ops[i][2];
        if (ops[i][0] == 0) {
            a[++len] = ops[i][2];
        }
    }
    sort(a + 1, a + 1 + len);
    int tmp = 1;
    for (int i = 2; i <= len; ++i) {
        if (a[i] != a[tmp]) {
            a[++tmp] = a[i];
        }
    }
    len = tmp;
    dfs(1, 0);
    for (int i = 1; i <= n; ++i) {
        arr[i] = get(arr[i]);
        add(dfn[i], arr[i], 1);
        add(dfn[i]+siz[i], arr[i], -1);
    }
    for (int i = 1; i <= m; ++i) {
        int k = ops[i][0], u = ops[i][1], v = ops[i][2];
        if (k == 0) {
            int l = dfn[u], r = dfn[u]+siz[u];
            // 首先区间[l,r]中的值域分布要少一个arr[u]
            add(l, arr[u], -1);
            add(r, arr[u], 1);
            // 然后更新arr[u]的值
            arr[u] = get(v);
            add(l, arr[u], 1);
            add(r, arr[u], -1);
        }
        else {
            int ans = solve(u, v, k);
            if (ans == -1) cout << "invalid request!" << endl;
            else cout << a[ans] << endl;
        }
    }
}