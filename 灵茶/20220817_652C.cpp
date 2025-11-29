#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 200003;

int n, m, arr[MAXN], pos[MAXN], b[MAXN];

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        pos[arr[i]] = i;
    }
    for (int i = 1, l, r; i <= m; ++i) {
        cin >> l >> r;
        if (pos[l] > pos[r]) swap(l, r);
        b[pos[r]] = max(b[pos[r]], pos[l]);
    }
    ll ans = 0, l = 0;
    for (int i = 1; i <= n; ++i) {
        if (l < b[i]) l = b[i];
        ans += i - l;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) solve();
}
