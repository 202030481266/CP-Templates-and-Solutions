// 树链剖分的泛化
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 5e5 + 7;
int n, k, top[maxn];
int son[maxn], a[maxn], f[maxn];
ll len[maxn];
vector<int> g[maxn];

void dfs1(int u, int fa) {
    f[u] = fa;
    for (int v : g[u]) {
        if (v != fa) {
            dfs1(v, u);
            if (len[v] > len[son[u]]) son[u] = v;
        }
    }
    len[u] = len[son[u]] + a[u];
}
void dfs2(int u, int t) {
    top[u] = t;
    if (!son[u]) return;
    dfs2(son[u], t);
    for (int v : g[u]) {
        if (v != son[u] && v != f[u]) dfs2(v, v);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 1);
    vector<ll> arr;
    for (int i = 1; i <= n; ++i) {
        if (top[i] == i) {
            arr.push_back(len[i]);
        }
    }
    int m = arr.size();
    if (m <= k) {
        cout << accumulate(arr.begin(), arr.end(), 0ll) << endl;    
    }
    else {
        k = m - k;
        nth_element(arr.begin(), arr.begin() + k - 1, arr.end());
        cout << accumulate(arr.begin() + k, arr.end(), 0ll) << endl;
    }
}