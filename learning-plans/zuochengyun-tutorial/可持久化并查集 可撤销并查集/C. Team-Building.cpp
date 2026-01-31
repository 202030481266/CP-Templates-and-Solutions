// https://codeforces.com/contest/1444/problem/C
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 5e5 + 7;
const int N = maxn * 2;
int fa[N], siz[N], stk[N][2], stkSize = 0;
int n, m, k, group[maxn], invalid[N];
vector<vector<int>> edges;

int find(int x) {
    while (x != fa[x]) {
        x = fa[x];
    }
    return x;
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (siz[fx] < siz[fy]) swap(fx, fy);
    fa[fy] = fx;
    siz[fx] += siz[fy];
    stk[stkSize][0] = fx;
    stk[stkSize++][1] = fy;
}

void rollback(int times) {
    for (int i = 1; i <= times; ++i) {
        int fx = stk[stkSize-1][0], fy = stk[stkSize-1][1];
        fa[fy] = fy;
        siz[fx] -= siz[fy];
        stkSize--;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> group[i];
    }
    for (int i = 1; i <= 2 * n; ++i) {
        fa[i] = i;
        siz[i] = 1;
    }
    // 解决组内之间的矛盾问题
    for (int i = 1, u, v; i <= m; ++i) {
        cin >> u >> v;
        if (group[u] != group[v]) {
            if (group[u] < group[v]) {
                edges.push_back({u, group[u], v, group[v]});
            }
            else {
                edges.push_back({v, group[v], u, group[u]});
            }
        }
        else {
            if (invalid[group[u]]) {
                continue;
            }
            int fu = find(u), fv = find(v);
            if (fu == fv) {
                --k;
                invalid[group[u]] = 1;
            }
            else {
                merge(u, v + n);
                merge(v, u + n);
            }
        }
    }
    sort(edges.begin(), edges.end(), [&](const vector<int> &a, const vector<int> &b) {
        return (a[1] != b[1]) ? a[1] < b[1] : a[3] < b[3];
    });
    ll ans = 1ll * k * (k - 1) / 2;
    int p = 0, N = edges.size();
    while (p < N) {
        int i = p + 1, gu = edges[p][1], gv = edges[p][3];
        while (i < N && edges[i][1] == gu && edges[i][3] == gv) ++i;
        // [p, i) is the same type edge
        if (!invalid[gu] && !invalid[gv]) {
            int ops = 0;
            for (int j = p; j < i; ++j) {
                int u = edges[j][0], v = edges[j][2];
                if (find(u) == find(v)) {
                    --ans;
                    break;
                }
                else {
                    merge(u, v + n);
                    merge(v, u + n);
                    ops += 2;
                }
            }
            rollback(ops);
        }
        p = i;
    }
    cout << ans << '\n';
}