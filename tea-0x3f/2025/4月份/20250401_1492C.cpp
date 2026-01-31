#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

void solve() {
    int n, m;
    string s, t;
    cin >> n >> m;
    cin >> s >> t;
    vector<int> first(m), last(m);
    int p = 0;
    for (int i = 0; i < n && p < m; ++i) {
        if (s[i] == t[p]) {
            first[p] = i;
            ++p;
        }
    }
    p = m - 1;
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == t[p]) {
            last[p] = i;
            --p;
        }
    }
    int ans = 0;
    for (int i = 0; i + 1 < m; ++i) {
        ans = max(ans, last[i+1] - first[i]);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}