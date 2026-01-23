// Problem: C. Zero Path
// Contest: Codeforces - Codeforces Round 801 (Div. 2) and EPIC Institute of Technology Round
// URL: https://codeforces.com/problemset/problem/1695/C
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

int arr[1000][1000];
using bs = bitset<1000>;
bs dp[2][1000];

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> arr[i][j];
            if (arr[i][j] < 0) arr[i][j] = 0;
        }
    }
    if (n + m - 1 & 1) {
        cout << "NO" << '\n';
        return;
    }
    int pre = 0, cur = 1, N = (n + m - 1) / 2;
    for (int i = 0; i < m; ++i) dp[pre][i].reset();
    dp[pre][0].set(0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) dp[cur][j].reset();
        for (int j = 0; j < m; ++j) {
            dp[cur][j].reset();
            if (arr[i][j]) {
                if (j > 0) dp[cur][j] |= dp[cur][j - 1] << 1;
                dp[cur][j] |= dp[pre][j] << 1;
            }
            else {
                if (j > 0) dp[cur][j] |= dp[cur][j - 1];
                dp[cur][j] |= dp[pre][j];
            }
        }
        swap(pre, cur);
    }
    cout << (dp[pre][m - 1].test(N) ? "YES" : "NO") << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}