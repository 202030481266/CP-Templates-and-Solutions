#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// 算是非常经典的一种左偏树的应用的结构了
const int maxn = 300010;
ll val[maxn], mul[maxn], add[maxn], h[maxn], a[maxn], v[maxn];
int ls[maxn], rs[maxn], dis[maxn], fa[maxn], f[maxn], c[maxn];
int n, m, root[maxn], dead[maxn], dep[maxn], cnt[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void pushdown(int rt) {
    if (!rt) return;
    if (mul[rt] != 1) {
        val[rt] = val[rt] * mul[rt];
        mul[ls[rt]] = mul[ls[rt]] * mul[rt];
        mul[rs[rt]] = mul[rs[rt]] * mul[rt];
        add[ls[rt]] = add[ls[rt]] * mul[rt];
        add[rs[rt]] = add[rs[rt]] * mul[rt];
        mul[rt] = 1;
    }
    if (add[rt]) {
        val[rt] = (val[rt] + add[rt]);
        add[ls[rt]] = (add[ls[rt]] + add[rt]);
        add[rs[rt]] = (add[rs[rt]] + add[rt]);
        add[rt] = 0;
    }
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    // 小根堆
    pushdown(x);
    pushdown(y);
    if (val[x] > val[y]) swap(x, y);
    rs[x] = merge(rs[x], y);
    if (dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);
    dis[x] = dis[rs[x]] + 1;
    fa[ls[x]] = fa[rs[x]] = x;
    return x;
}

int pop(int x) {
    pushdown(x); // 先下传
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    // lazy set
    fa[x] = merge(ls[x], rs[x]);
    ls[x] = rs[x] = dis[x] = 0;
    return fa[x]; // 返回新的堆顶
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m; 
    vector<int> g[n+1];
    for (int i = 1; i <= n; ++i) cin >> h[i];
    for (int i = 2; i <= n; ++i) {
        cin >> f[i] >> a[i] >> v[i];
        g[f[i]].push_back(i);
    }
    dis[0] = -1;
    for (int i = 1; i <= m; ++i) {
        cin >> val[i] >> c[i];
        fa[i] = i;
        mul[i] = 1;
        dead[i] = -1;
        root[c[i]] = merge(root[c[i]], i);
    }
    
    for (int i = n; i >= 1; --i) {
        int rt = root[i], res = 0;
        while (rt) {
            pushdown(rt);
            if (val[rt] >= h[i]) break;
            ++res;
            dead[rt] = i;
            rt = pop(rt);
        }
        cnt[i] = res;
        if (i > 1 && rt) {
            if (!a[i]) {
                add[rt] = add[rt] + v[i];
            }
            else {
                mul[rt] = mul[rt] * v[i];
                add[rt] = add[rt] * v[i];
            }
            root[f[i]] = merge(root[f[i]], rt);
        }
    }
    queue<int> q;
    q.push(1);
    dep[1] = 1;
    while (!q.empty()) {
        int u = q.front(); 
        q.pop();
        for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            dep[v] = dep[u] + 1;
            q.push(v);
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << cnt[i] << '\n';
    }
    for (int i = 1; i <= m; ++i) {
        if (dead[i] == -1) {
            cout << dep[c[i]] << '\n';
        }
        else {
            cout << dep[c[i]] - dep[dead[i]] << '\n';
        }
    }
    return 0;
}

