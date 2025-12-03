#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

static constexpr int MAXN = 300005;
static constexpr int MOD = 998244353;

int n, a[MAXN], b[MAXN];
pii arr[MAXN];
ll ans = 1;
ll fac[MAXN];

template<typename T>
ll cal(T num[]) {
    sort(num + 1, num + 1 + n);
    int p = 1;
    ll res = 1;
    while (p <= n) {
        int i = p + 1;
        while (i <= n && num[i] == num[p]) ++i;
        res = res * fac[i - p] % MOD;
        p = i;
    }
    return res;
}

void solve() {
    cin >> n;
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        a[i] = arr[i].first;
        b[i] = arr[i].second;
    }
    ll r1 = cal(a);
    ll r2 = cal(b);
    ll ans = r1 + r2;
    sort(arr + 1, arr + 1 + n);
    bool flag = true;
    for (int i = 2; i <= n; ++i) {
        if (arr[i].second < arr[i - 1].second) {
            flag = false;
            break;
        }
    }
    if (flag) ans -= cal(arr);
    ans = fac[n] - ans;
    cout << (ans % MOD + MOD) % MOD << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}
