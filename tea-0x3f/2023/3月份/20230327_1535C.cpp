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
    string s;
    cin >> s;
    int n = s.size();
    vl dp(n);
    dp[0] = 1;
    ll ans = 1;
    int last = s[0] == '?' ? -1 : 0;
    for (int i = 1; i < n; ++i) {
        dp[i] = 1;
        if (s[i] == '1') {
            if (s[i - 1] == '0') dp[i] += dp[i - 1];
            else if (s[i - 1] == '?') {
                if (last != -1 && ((i - last - 1 & 1) ^ (s[i] - '0' ^ s[last] - '0'))) dp[i] += dp[i - 1];
                else dp[i] = i - last;
            }
            last = i;
        }
        else if (s[i] == '0') {
            if (s[i - 1] == '1') dp[i] += dp[i - 1];
            else if (s[i - 1] == '?') {
                if (last != -1 && ((i - last - 1 & 1) ^ (s[i] - '0' ^ s[last] - '0'))) dp[i] += dp[i - 1];
                else dp[i] = i - last;
            }
            last = i;
        }
        else {
            dp[i] += dp[i - 1];
        }
        ans += dp[i];
    }
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}