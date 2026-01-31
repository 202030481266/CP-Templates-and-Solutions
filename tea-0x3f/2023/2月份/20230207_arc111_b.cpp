#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;

void solve() {
    int n;
    cin >> n;
    vii arr(n, vi(2));
    int mx = 0;
    for (auto& v : arr) {
        cin >> v[0] >> v[1];
        if (v[0] > v[1]) swap(v[0], v[1]);
        mx = max(mx, v[1]);
    }
    vi fa(mx + 1);
    auto find = [&](int x) -> int {
        int root = x;
        while (fa[root] != root) root = fa[root];
        while (fa[x] != x) {
            int nxt = fa[x];
            fa[x] = root;
            x = nxt;
        }
        return root;
    };
    vi cnt(mx + 1), siz(mx + 1);
    for (int i = 1; i <= mx; ++i) {
        fa[i] = i;
        siz[i] = 1;
    }
    for (auto v : arr) {
        int f0 = find(v[0]);
        int f1 = find(v[1]);
        if (f1 != f0) {
            fa[f0] = f1;
            cnt[f1] += cnt[f0];
            siz[f1] += siz[f0];
        }
        ++cnt[f1];
    }
    int ans = 0;
    for (int i = 1; i <= mx; ++i) {
        int f = find(i);
        if (cnt[f]) {
            ans += min(cnt[f], siz[f]);
            cnt[f] = 0;
        }
    }        
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
