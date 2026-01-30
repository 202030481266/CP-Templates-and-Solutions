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
    int n, m;
    cin >> n >> m;
    vii val(n + 1);
    vi sz(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> sz[i];
        auto& con = val[i];
        con.resize(sz[i] + 1);
        vi sum(sz[i] + 1);
        vi arr(sz[i] + 1);
        for (int p = 1; p <= sz[i]; ++p) {
            cin >> arr[p];
            sum[p] = sum[p - 1] + arr[p];
        }
        con[sz[i]] = sum[sz[i]];
        for (int b = 1; b < sz[i]; ++b) {
            for (int x = 0; x <= b; ++x) {
                // suf = b - x, (sz[i] - suf, sz[i]] -> (sz[i] - b + x, sz[i]]
                con[b] = max(con[b], sum[x] + sum[sz[i]] - sum[sz[i] - b + x]);
            }
        }
    }
    vi dp(m + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; --j) {
            for (int k = 1; k <= min(j, sz[i]); ++k) {
                if (dp[j - k] + val[i][k] > dp[j]) dp[j] = dp[j - k] + val[i][k];
            }
        }
    }
    cout << dp[m] << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
