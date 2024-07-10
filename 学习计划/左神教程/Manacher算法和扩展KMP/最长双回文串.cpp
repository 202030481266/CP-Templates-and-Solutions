// https://www.luogu.com.cn/problem/P4555

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

const int N = 2e5 + 10;
int dp[N], n, mx[N], f[N], g[N];
string s, ss;

int solve() {
    cin >> ss;
    s.assign(2*ss.size()+1,'#');
    for (int i = 0; i < ss.size(); ++i) {
        s[2*i + 1] = ss[i];
    }
    n = s.size();
    for (int i = 0; i < n; ++i) mx[i] = g[i] = 1; // at lease is 1
    for (int i = 0, c = 0, r = 0; i < n; ++i) {
        dp[i] = i < r ? min(r-i, dp[2*c-i]) : 1;
        while (i-dp[i] >= 0 && i+dp[i] < n && s[i-dp[i]] == s[i+dp[i]]) {
            mx[i+dp[i]] = max(mx[i+dp[i]], dp[i]+1); // only update when expand, and so r is
            dp[i]++;
        }
        if (i + dp[i] > r) {
            r = i + dp[i];
            c = i;
        }
    }
    // reverse manacher
    for (int i = n-1, c = n-1, r = n-1; i >= 0; --i) {
        // (r, i]
        f[i] = i > r ? min(i-r, dp[2*c-i]) : 1;
        while (i+f[i] < n && i-f[i] >= 0 && s[i+f[i]] == s[i-f[i]]) {
            g[i-f[i]] = max(g[i-f[i]], f[i]+1);
            f[i]++;
        }
        if (i-f[i] < r) {
            r = i - f[i];
            c = i;
        }
    }
    int ans = 0;
    for (int i = 1; i < n-2; ++i) { // last char and first char both are '#', so we needn't consider them
        if (s[i] == '#') {
            ans = max(ans, mx[i] + g[i] - 2);
        }
    }
    return ans;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve() << endl;
}