// Problem: C. Vladik and Memorable Trip
// Contest: Codeforces - Codeforces Round 416 (Div. 2)
// URL: https://codeforces.com/problemset/problem/811/C
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
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

int n, arr[5003], dp[5003], lo[5003], up[5003];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> arr[i];
    for (int i = 1; i <= n; ++i) {
        if (!lo[arr[i]]) lo[arr[i]] = i;
        up[arr[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];
        if (up[arr[i]] != i) continue;
        int l = lo[arr[i]], j = i, flag = 1, _xor = 0;
        while (j >= l) {
            if (up[arr[j]] > i) {
                flag = 0;
                break;
            }
            l = min(l, lo[arr[j]]);
            if (j == lo[arr[j]]) _xor ^= arr[j];
            --j;
        }
        if (flag) dp[i] = max(dp[i], _xor + dp[j]);
    }    
    cout << dp[n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}