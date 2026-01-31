#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1e5 + 7;
int fa[maxn]; 
ll dis[maxn];
int n, m, q;

int find(int x) {
    if (x == fa[x]) return x;
    int f = fa[x];
    fa[x] = find(fa[x]);
    dis[x] += dis[f];
    return fa[x];
}
void merge(int u, int v, ll w) {
    int fu = find(u), fv = find(v);
    if (fu == fv) return;
    fa[fu] = fv;
    dis[fu] = dis[v] - dis[u] + w;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m >> q;
    int l, r;
    ll s;
    ++n;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r >> s;
        // l -> r+1, v
        merge(l, r+1, s);
    }
    for (int i = 0; i < q; ++i) {
        cin >> l >> r;
        int fl = find(l), fr = find(r+1);
        if (fl != fr) cout << "UNKNOWN" << endl;
        else {
            cout << dis[l] - dis[r+1] << endl;
        }
    }
}