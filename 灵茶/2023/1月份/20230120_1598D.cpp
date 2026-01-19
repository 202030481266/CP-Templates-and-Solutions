// Problem: D. Training Session
// Contest: Codeforces - Educational Codeforces Round 115 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1598/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

ll C(ll N, int b) {
    if (b == 2) return N * (N - 1) / 2;
    return N * (N - 1) * (N - 2) / 6;
}

void solve() {
    int n;
    cin >> n;
    vector<pii> arr(n);
    for (auto& [x, y] : arr) cin >> x >> y;
    ranges::sort(arr);
    vl cnt(n + 1);
    for (int i = 0; i < n; ++i) cnt[arr[i].second]++;
    int p = 0;
    ll res = 0;
    while (p < n) {
        int i = p + 1;
        while (i < n && arr[i].first == arr[p].first) ++i;
        for (int x = p; x < i; ++x) --cnt[arr[x].second];
        int j = p;
        while (j < i) {
            int k = j + 1;
            while (k < i && arr[k] == arr[j]) ++k;
            if (k - j >= 3) res += C(k - j, 3);
            if (k - j >= 2) res += C(k - j, 2) * (n - k + j);
            res += 1LL * (k - j) * (i - p - k + j) * cnt[arr[j].second];
            j = k;
        }
        for (int x = p; x < i; ++x) ++cnt[arr[x].second];
        p = i;
    } 
    ll tot = C(n, 3);
    cout << tot - res << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}