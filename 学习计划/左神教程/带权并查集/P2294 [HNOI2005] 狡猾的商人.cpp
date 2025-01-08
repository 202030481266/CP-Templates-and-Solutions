#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int maxn = 1007;
int fa[maxn];
ll dis[maxn];

int find(int x) {
    if (fa[x] == x) return x;
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
    int t, n, m;
    int l, r, s;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        ++n;
        for (int i = 1; i <= n; ++i) fa[i] = i, dis[i] = 0;
        bool ans = true;
        while (m--) {
            cin >> l >> r >> s;
            if (!ans) continue;
            int fl = find(l), fr = find(r+1);
            if (fl == fr) {
                if (dis[l] - dis[r+1] != s) {
                    ans = false;
                }
            }
            else {
                merge(l, r+1, s);
            }
        }
        cout << (ans ? "true" : "false") << endl;
    }
}