// Problem: D. Remove One Element
// Contest: Codeforces - Codeforces Round 605 (Div. 3)
// URL: https://codeforces.com/contest/1272/problem/D
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

void solve() {
    int n;
    cin >> n;
    vi arr(n + 1);
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    vi pre(n + 1);
    vi suf(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i > 1 && arr[i] > arr[i - 1]) pre[i] = pre[i - 1] + 1;
        else pre[i] = 1;
    }
    for (int i = n; i >= 1; --i) {
        if (i < n && arr[i] < arr[i + 1]) suf[i] = suf[i + 1] + 1;
        else suf[i] = 1;
    }
    int ans = *ranges::max_element(pre);
    for (int i = 2; i < n; ++i) {
        if (arr[i - 1] < arr[i + 1]) ans = max(ans, pre[i - 1] + suf[i + 1]);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}