// 主要是添加了一个删除指定数字的操作，需要修改沿途的路径

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int maxn = 2e6 + 7;
int t, w, n, m;
ll k, val[maxn];
int ls[maxn], rs[maxn], dis[maxn];
int fa[maxn]; 
int pa[maxn];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y) {
    if (!x || !y) return x + y;
    // make sure x is the root
    if (val[x] < val[y] || (val[x] == val[y] && x > y)) 
        swap(x, y);
    // dfs
    rs[x] = merge(rs[x], y);
    // set the parent
    pa[rs[x]] = x;
    // set the distance
    if (dis[ls[x]] < dis[rs[x]]) swap(ls[x], rs[x]);
    dis[x] = dis[rs[x]] + 1;
    // set the fa relationship
    fa[ls[x]] = fa[rs[x]] = x;
    return x;
}

int remove(int x) {
    int rt = find(x);
    // split
    fa[ls[x]] = ls[x];
    fa[rs[x]] = rs[x];
    // merge
    int mg = merge(ls[x], rs[x]);
    // set the fa relationship, lazy update
    fa[x] = mg;
    // set the parent
    int par = pa[x];
    pa[mg] = par;

    if (rt != x) {
        // set the fa relationship
        fa[mg] = rt;
        // set the parent and son relationship
        if (ls[par] == x) ls[par] = mg;
        else rs[par] = mg;
        // set the distance
        for (int d = dis[mg]; dis[par] > d + 1; par = pa[par], ++d) {
            dis[par] = d + 1;
            if (dis[ls[par]] < dis[rs[par]]) swap(ls[par], rs[par]);
        }
    }
    // clear the node
    ls[x] = rs[x] = pa[x] = dis[x] = 0;
    return fa[mg]; // return the root
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t >> w >> k;
    while (t--) {
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            cin >> val[i];
            ls[i] = rs[i] = pa[i] = dis[i] = 0;
            fa[i] = i;
        }
        int op, x, y; 
        while (m--) {
            cin >> op;
            if (op == 2) {
                cin >> x;
                int rt = remove(x);
                val[x] = 0;
                fa[rt] = fa[x] = merge(rt, x);
            }
            else if (op == 3) {
                cin >> x >> y;
                x = find(x);
                int rt = remove(x);
                val[x] = max(0ll, val[x]-y);
                fa[rt] = fa[x] = merge(rt, x);
            }
            else {
                cin >> x >> y;
                int fx = find(x), fy = find(y);
                if (fx == fy) continue;
                merge(fx, fy); // fx, fy will be the root
            }
        }
        ll ans = 0, mx = 0;
        for (int i = 1; i <= n; ++i) {
            if (find(i) == i) {
                mx = max(mx, val[i]);
                ans += val[i];
            }
        }
        if (w == 2) ans -= mx;
        else if (w == 3) ans += mx;
        if (ans == 0) cout << "Gensokyo " << ans << '\n';
        else if (ans > k) cout << "Hell " << ans << '\n';
        else cout << "Heaven " << ans << '\n';
    }
    return 0;
}