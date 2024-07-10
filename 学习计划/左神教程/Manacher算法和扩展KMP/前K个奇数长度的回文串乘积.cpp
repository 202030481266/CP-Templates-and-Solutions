// https://www.luogu.com.cn/problem/P1659 

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int mod = 19930726;
const int inf = 0x3f3f3f3f;

const int N = 2e6 + 10;
ll dp[N], n, k, m, mx, cnt[N>>1];
string s, ss;

ll cal(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}

ll solve() {
    cin >> n >> k >> ss;
    s.assign(2*n+1,'#');
    for (int i = 0; i < n; ++i) {
        s[2*i + 1] = ss[i];
    }
    m = 2*n+1;
    for (int i = 0, c = 0, r = 0; i < m; ++i) {
        dp[i] = (i < r ? min(dp[2*c - i], (ll)r-i) : 1);
        while (i-dp[i] >= 0 && i+dp[i] < m && s[i-dp[i]] == s[i+dp[i]]) ++dp[i];
        if (i + dp[i] > r) {
            r = i + dp[i];
            c = i;
        }
        ll len = dp[i]-1;
        if (len & 1) {
            mx = max(mx, len);
            ++cnt[len];
        }
    }
    
    ll cur = 0, ans = 1, sum = 0, inc;
    for (int i = mx; i >= 1 && sum < k; i -= 2) {
        cur += cnt[i];	
        inc = (sum+cur >= k ? k-sum : cur);
        ans = ans * cal(i, inc) % mod;
        sum += inc;
    }
    return (sum >= k ? ans : -1);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << solve() << endl;
}