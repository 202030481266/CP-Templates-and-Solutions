// P6088 [JSOI2015] 字符串树
// https://www.luogu.com.cn/problem/P6088

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 1e5 + 7;
const int N = maxn * 20;
const int B = 26;
int root[maxn], tot, tree[N][B], cnt[N];
int n, m, dep[maxn], fa[maxn][20];
vector<pair<int,string>> g[maxn];

int insert(string& s, int x) {
    int rt = ++tot;
    for (int i = 0; i < B; ++i) {
        tree[rt][i] = tree[x][i];
    }
    cnt[rt] = cnt[x] + 1;
    for (int i = 0, pre = rt, cur, b; i < s.size(); ++i) {
        b = s[i] - 'a';
        x = tree[x][b];
        cur = ++tot;
        for (int j = 0; j < B; ++j) {
            tree[cur][j] = tree[x][j];
        }
        cnt[cur] = cnt[x] + 1;
        tree[pre][b] = cur;
        pre = cur;
    }
    return rt;
}

int query(string& s, int x) {
    for (int i = 0, b; i < s.size(); ++i) {
        b = s[i] - 'a';
        x = tree[x][b];
        if (!x) return 0;
    }
    return cnt[x];
}

void dfs1(int u, int father, string& w) {
    dep[u] = dep[father] + 1;
    fa[u][0] = father;
    root[u] = insert(w, root[father]);
    for (int i = 1; i < 20; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (auto [v, s] : g[u]) {
        if (v != father) {
            dfs1(v, u, s);
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    }
    return fa[x][0];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    string s, prefix, empty;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v >> s;
        g[u].push_back({v, s});
        g[v].push_back({u, s});
    }
    dfs1(1, 0, empty);
    cin >> m;
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v >> prefix;
        int l = lca(u, v);
        cout << query(prefix, root[u]) + query(prefix, root[v]) - query(prefix, root[l]) * 2 << '\n';
    }
}