// Problem: D. Points and Powers of Two
// Contest: Codeforces - Codeforces Round 486 (Div. 3)
// URL: https://codeforces.com/contest/988/problem/D
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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
    vl arr(n);
    for (ll& v : arr) cin >> v;
    if (n == 1) {
        cout << 1 << '\n' << arr[0] << '\n';
        return;
    }
    ranges::sort(arr);
    pii res = {-1, -1};
    ll sub = arr[n - 1] - arr[0];
    if ((sub & -sub) == sub) res = {arr[0], arr[n - 1]};
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < 31; ++k) {
            ll pre = arr[i] - (1 << k);
            ll nxt = arr[i] + (1 << k);
            if (nxt > arr[n - 1] || pre < arr[0]) break;
            auto pit = lower_bound(arr.begin(), arr.begin() + i, pre) - arr.begin();
            auto nit = lower_bound(arr.begin() + i + 1, arr.end(), nxt) - arr.begin();
            if (pit != i && nit != n && arr[pit] == pre && arr[nit] == nxt) {
                cout << 3 << '\n';
                cout << pre << ' ' << arr[i] << ' ' << nxt << '\n';
                return;
            }
            if (pit != i && arr[pit] == pre) res = {pre, arr[i]};
            if (nit != n && arr[nit] == nxt) res = {arr[i], nxt};
        }
    }
    if (res.first != -1 || res.second != -1) {
        cout << 2 << '\n' << res.first << ' ' << res.second << '\n';
        return;
    }
    cout << 1 << '\n' << arr[0] << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
