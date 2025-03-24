#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 2e5 + 7;
int n, color[maxn], L[maxn], R[maxn], cnt[maxn];
int val[maxn], son[maxn], siz[maxn], ids[maxn], dfn = 0, ans = 0;
vector<int> g[maxn];

void add(int x) {
    cnt[color[x]]--;
    color[x]++;
    cnt[color[x]]++;
}
void del(int x) {
    cnt[color[x]]--;
    color[x]--;
    assert(color[x] >= 0);
    cnt[color[x]]++;
}
void dfs0(int u) {
    L[u] = ++dfn;
    ids[dfn] = u;
    siz[u] = 1;
    for (int v : g[u]) {
        dfs0(v);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
    R[u] = dfn;
}
void dfs1(int u, int keep) {
    for (int v : g[u]) {
        if (v != son[u]) dfs1(v, 0);
    }
    if (son[u]) dfs1(son[u], 1);
    add(val[u]);
    for (int v : g[u]) {
        if (v != son[u]) {
            for (int i = L[v]; i <= R[v]; ++i) add(val[ids[i]]);
        }
    }
    if (cnt[color[val[u]]] * color[val[u]] == siz[u]) ++ans;
    if (!keep) {
        for (int i = L[u]; i <= R[u]; ++i) del(val[ids[i]]);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1, fa; i <= n; ++i) {
        cin >> val[i] >> fa;
        g[fa].push_back(i);
    }
    dfs0(1);
    dfs1(1, 1);
    cout << ans << '\n';
}