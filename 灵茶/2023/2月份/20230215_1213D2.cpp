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
    int n, k;
    cin >> n >> k;
    vi a(n);
    for (int& v : a) cin >> v;
    int mx = *ranges::max_element(a);
    vii g(mx + 1);
    for (int v : a) {
        int use = 0;
        while (v) {
            g[v].push_back(use);
            ++use;
            v >>= 1;
        }
    }
    int ans = INF;
    for (int i = 1; i <= mx; ++i) {
        if (g[i].size() >= k) {
            nth_element(g[i].begin(), g[i].begin() + k, g[i].end());
            int res = 0;
            for (int j = 0; j < k; ++j) res += g[i][j];
            ans = min(ans, res);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
