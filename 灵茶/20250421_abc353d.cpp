// https://atcoder.jp/contests/abc353/tasks/abc353_d
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int mod = 998244353;

void solve() {
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (ll& v : arr) cin >> v;
    
    vector<ll> p10(11);
    p10[0] = 1;
    for (int i = 1; i < 11; ++i) {  // 修正：应该是 i < 11
        p10[i] = 10 * p10[i - 1] % mod;
    }
    
    ll cur = 0, sum = 0;
    for (ll v : arr) {
        int len = to_string(v).size();
        cur = (cur + p10[len]) % mod;
        sum = (sum + v) % mod;
    }
    
    ll ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        int len = to_string(arr[i]).size();  // 修正：使用 arr[i] 而不是 v
        cur = ((cur - p10[len]) % mod + mod) % mod;
        sum = ((sum - arr[i]) % mod + mod) % mod;
        ans = (ans + cur * arr[i] % mod + sum) % mod;
    }
    
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}