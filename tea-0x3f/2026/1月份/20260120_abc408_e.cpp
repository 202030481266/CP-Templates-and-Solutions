#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

int fa[200005];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, int>> edges(m);
    int mx = 0;
    for (auto& [u, v, w] : edges) {
        cin >> u >> v >> w;
        mx = max(mx, w);
    }
    int wid = bit_width(1u * mx);
    int mask = 0;
    for (int i = wid - 1; i >= 0; --i) {
        mask ^= 1 << i;
        iota(fa + 1, fa + 1 + n, 1);
        for (auto [u, v, w] : edges) {
            if ((w & mask) == 0) {
                int fu = find(u);
                int fv = find(v);
                if (fu != fv) {
                    fa[fu] = fv;
                }
            }
        }
        if (find(1) != find(n)) mask ^= 1 << i;
    }
    cout << ((1 << wid) - 1 ^ mask) << '\n';
}
                
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

