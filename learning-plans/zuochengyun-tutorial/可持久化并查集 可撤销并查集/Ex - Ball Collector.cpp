// https://atcoder.jp/contests/abc302/tasks/abc302_h

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll llinf = 0x3f3f3f3f3f3f3f3f;

const int maxn = 2e5 + 7;
int n, m, fa[maxn], siz[maxn], edges[maxn], stk[maxn][2], stkSize = 0; 
int balls[maxn][2], ans[maxn];
vector<int> g[maxn];

int find(int x) {
    while (x != fa[x]) x = fa[x];
    return x;
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    if (siz[fx] < siz[fy]) swap(fx, fy);
    fa[fy] = fx;
    siz[fx] += siz[fy];
    edges[fx] += edges[fy] + 1;
    stk[stkSize][0] = fx;
    stk[stkSize++][1] = fy;
}
void rollback(int times=1) {
    for (int i = 1; i <= times; ++i) {
        int fx = stk[stkSize-1][0], fy = stk[stkSize-1][1];
        fa[fy] = fy;
        siz[fx] -= siz[fy];
        edges[fx] -= edges[fy] + 1;
        stkSize--;
    }
}
int cur = 0;
void dfs(int u, int father) {
    int A = balls[u][0], B = balls[u][1], fA = find(A), fB = find(B);
    bool add = false, un = false;
    if (fA == fB) {
        if (edges[fA] < siz[fA]) {
            cur++;
            add = true;
        }
        edges[fA]++;
    }
    else {
        if (edges[fA] < siz[fA] || edges[fB] < siz[fB]) {
            cur++;
            add = true;
        }
        merge(fA, fB); 
        un = true;
    }
    ans[u] = cur;
    for (int v : g[u]) {
        if (v != father) {
            dfs(v, u);
        }
    }
    if (add) cur--;
    if (un) rollback();
    else edges[fA]--;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> balls[i][0] >> balls[i][1];
        fa[i] = i;
        siz[i] = 1;
    } 
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 2; i <= n; ++i) {
        if (i < n) cout << ans[i] << ' ';
        else cout << ans[i] << '\n';
    }
}