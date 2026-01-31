#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;


void solve() {
    int n;
    cin >> n;
    vi ans(n + 1);
    int w = bit_width(1u * n);
    vi use(n + 1);
    if (n & 1) {
        ans[n] = n;
        ans[n - 1] = n - 1;
        ans[n - 2] = 3;
        ans[n - 3] = 1;
        for (int i = n; i >= n - 4; --i) use[ans[i]] = 1;
    }
    else {
        ans[n] = 1 << w - 1;
        ans[n - 1] = ans[n] - 1;
        ans[n - 2] = ans[n - 1] - 1;
        ans[n - 3] = 5;
        ans[n - 4] = 1;
        for (int i = n; i >= n - 4; --i) use[ans[i]] = 1;
    }
    for (int i = 1, j = 1; i <= n; ++i) {
        if (use[i]) continue;
        ans[j] = i;
        ++j;
    }
    cout << (n & 1 ? n : (1 << w) - 1) << '\n';
    // int res = 0;
    // for (int i = 1; i <= n; ++i) {
    //     if (i & 1) res &= ans[i];
    //     else res |= ans[i];
    // }
    // cout << res << '\n';
    for (int i = 1; i <= n; ++i) cout << ans[i] << (i == n ? '\n' :  ' ');
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
