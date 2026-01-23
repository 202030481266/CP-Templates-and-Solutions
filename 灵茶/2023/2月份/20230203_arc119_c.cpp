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
    vi arr(n + 1);
    vl sum(n + 1);
    vector<pair<ll, int>> b;
    b.emplace_back(0, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        sum[i] = sum[i - 1] + (i & 1 ? arr[i] : -arr[i]);
        b.emplace_back(sum[i], i);
    }
    ranges::sort(b);
    vi rank(n + 1);
    int cur = 0;
    for (int i = 0; i < (int)b.size(); ++i) {
        if (i == 0 || b[i].first != b[i - 1].first) ++cur;
        rank[b[i].second] = cur;
    }
    vi cnt(cur + 1);
    ll ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans += cnt[rank[i]];
        ++cnt[rank[i]];
    }
    cout << ans << '\n';
}
        
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}

