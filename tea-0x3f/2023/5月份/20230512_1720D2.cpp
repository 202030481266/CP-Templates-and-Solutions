// Problem: D2. Xor-Subsequence (hard version)
// Contest: Codeforces - Codeforces Round 815 (Div. 2)
// URL: https://codeforces.com/contest/1720/problem/D2
// Memory Limit: 512 MB
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
static constexpr int MAXN = 300005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

static constexpr int MAX_BIT = 29;
static constexpr int MAX_NODE = MAXN * MAX_BIT; 

int tree[MAX_NODE][2];
int mx[MAX_NODE][4];
int tot = 0;

int alloc() {
    ++tot;
    tree[tot][0] = tree[tot][1] = 0;
    mx[tot][0] = mx[tot][1] = mx[tot][2] = mx[tot][3] = 0;
    return tot;
}

void init() {
    tot = 0;
    tree[0][0] = tree[0][1] = 0;
    mx[tot][0] = mx[tot][1] = mx[tot][2] = mx[tot][3] = 0;
}

void solve() {
    // dp[i] = max(dp[j]) + 1 if aj ^ i < ai ^ j
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    init();
    vi dp(n);
    for (int i = 0; i < n; ++i) {
        // (ai, i)
        int u = 0;
        for (int j = MAX_BIT; j >= 0; --j) {
            int x = arr[i] >> j & 1;
            int y = i >> j & 1;
            int k = x << 1 | y;
            if (k == 0) dp[i] = max(dp[i], mx[u][1]);
            if (k == 1) dp[i] = max(dp[i], mx[u][3]);
            if (k == 2) dp[i] = max(dp[i], mx[u][0]);
            if (k == 3) dp[i] = max(dp[i], mx[u][2]);
            if (!tree[u][x ^ y]) break;
            u = tree[u][x ^ y];
        }
        ++dp[i];
        u = 0;
        for (int j = MAX_BIT; j >= 0; --j) {
            int x = arr[i] >> j & 1;
            int y = i >> j & 1;
            int k = x << 1 | y;
            mx[u][k] = max(mx[u][k], dp[i]);
            if (!tree[u][x ^ y]) tree[u][x ^ y] = alloc();
            u = tree[u][x ^ y];
        }
    }
    int ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
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