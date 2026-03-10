// Problem: C. Game Master
// Contest: Codeforces - Codeforces Round 758 (Div.1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/1608/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    for (int& v : a) cin >> v;
    for (int& v : b) cin >> v;
    vector<pii> arr;
    for (int i = 0; i < n; ++i) arr.emplace_back(b[i], i);
    ranges::sort(arr);
    int cur = 0;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || arr[i].first != arr[i - 1].first) ++cur;
        b[arr[i].second] = cur;
    }
    vi mx(cur + 1);
    for (int i = 0; i < n; ++i) {
        mx[b[i]] = max(mx[b[i]], a[i]);
    }
    for (int i = 1; i <= cur; ++i) mx[i] = max(mx[i], mx[i - 1]);
    vi c(n);
    iota(c.begin(), c.end(), 0);
    ranges::sort(c, [&](const int& i, const int& j){ return a[i] != a[j] ? a[i] < a[j] : b[i] < b[j]; });
    auto check = [&](int start) -> bool {
        int val = 0, x = 0;
        for (int i = 0; i <= start; ++i) val = max(val, b[c[i]]);
        int p = start;
        x = mx[val];
        while (p < n - 1) {
            int i = p + 1;
            while (i < n && a[c[i]] <= x) ++i;
            for (int j = p + 1; j < i; ++j) val = max(val, b[c[j]]);
            x = mx[val];
            if (i - p == 1) return false;
            p = i - 1;
        }
        return true;
    };
    int l = -1, r = n;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid;
    }
    vi ans(n);
    for (int i = r; i < n; ++i) ans[c[i]] = 1;
    for (int v : ans) cout << v;
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}