// Problem: B. Johnny and Grandmaster
// Contest: Codeforces - Codeforces Round 647 (Div. 1) - Thanks, Algo Muse!
// URL: https://codeforces.com/problemset/problem/1361/B
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
using vl = vector<long long>;
using vll = vector<vector<long long>>;
static constexpr int INF = 0x3f3f3f3f;
static constexpr ll LLINF = 0x3f3f3f3f3f3f3f3f;
static constexpr int MOD = 1e9 + 7;

ll pw(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
    }
    return res;
}

void solve() {
    int n, p;
    cin >> n >> p;
    vi arr(n);
    for (int& v : arr) cin >> v;
    ranges::sort(arr);
    if (p == 1) {
        cout << (n & 1 ? 1 : 0) << '\n';
        return;
    }
    ll cur = 0;
    ll A = 0, B = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (cur > 0 && i < n - 1 && arr[i] != arr[i + 1]) {
            int sub = arr[i + 1] - arr[i];
            // cur = cur * p ^ sub;
            while (cur < i + 1 && sub--) cur *= p;
        }
        if (cur >= i + 1) {
            for (int j = i; j >= 0; --j) {
                B = (B + pw(p, arr[j])) % MOD;
            }
            break;
        }
        if (cur > 0) {
            B = (B + pw(p, arr[i])) % MOD;
            --cur;
        }
        else {
            A = (A + pw(p, arr[i])) % MOD;
            ++cur;
        }
    }
    ll ans = ((A - B) % MOD + MOD) % MOD;
    cout << ans << '\n';
}
            

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
