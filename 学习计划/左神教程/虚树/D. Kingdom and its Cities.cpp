#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100003;
static constexpr int INF = 0x3f3f3f3f;

int n, m, arr[MAXN << 1], dfn[MAXN], tot = 0;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], weight[MAXN << 1], ecnt = 0;
int headv[MAXN], nxtv[MAXN], tov[MAXN], weightv[MAXN], vcnt = 0;

void addEdge(int u, int v, int w) {
    to[++ecnt] = v;
    weight[ecnt] = w;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

void addEdgeV(int u, int v, int w) {
    tov[++vcnt] = v;
    weightv[vcnt] = w;
    nxtv[vcnt] = headv[u];
    headv[u] = vcnt;
}

int f[MAXN][20], dep[MAXN], vis[MAXN];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = ++tot;
    f[u][0] = fa;
    for (int i = 1; i < 20; ++i) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v != fa) dfs(v, u);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

int buildVirtualTree(int k) {
    sort(arr, arr + k, [&](int i, int j) { return dfn[i] < dfn[j]; }); // sort by dfn
    vector<int> tmp;
    tmp.push_back(arr[0]);
    for (int i = 1; i < k; ++i) {
        tmp.push_back(lca(arr[i - 1], arr[i])); // add lca
        tmp.push_back(arr[i]);
    }
    ranges::sort(tmp, [&](int i, int j) { return dfn[i] < dfn[j]; }); // sort by dfn
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    for (int i = 0; i < tmp.size(); ++i) headv[tmp[i]] = 0;
    vcnt = 0; // initialize the tree
    for (int i = 1; i < tmp.size(); ++i) {
        int l = lca(tmp[i - 1], tmp[i]);
        addEdgeV(l, tmp[i], 1);
    }
    return tmp[0]; // root
}

bool check(int u) {
    for (int i = headv[u]; i; i = nxtv[i]) {
        if (vis[tov[i]] && vis[u] && (f[u][0] == tov[i] || f[tov[i]][0] == u)) return false;
        if (!check(tov[i])) return false;
    }
    return true;
}

int ans;

int solve(int u) {
    int sum = 0;
    for (int i = headv[u]; i; i = nxtv[i]) {
        int r = solve(tov[i]);
        if (r) {
            if (vis[u]) ++ans;
            else ++sum;
        }
    }
    if (sum > 1) {
        ++ans;
        return 0;
    }
    return vis[u] || sum > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        addEdge(u, v, 1);
        addEdge(v, u, 1);
    }
    dfs(1, 0);
    cin >> m;
    for (int i = 0, k; i < m; ++i) {
        cin >> k;
        for (int j = 0; j < k; ++j) {
            cin >> arr[j];
            vis[arr[j]] = 1;
        }
        int root = buildVirtualTree(k);
        if (!check(root)) {
            cout << -1 << '\n';
        }
        else {
            ans = 0;
            solve(root);
            cout << ans << '\n';
        }
        for (int j = 0; j < k; ++j) vis[arr[j]] = 0;
    }
}