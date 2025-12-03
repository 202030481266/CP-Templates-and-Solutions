// https://codeforces.com/problemset/problem/1994/C
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int maxn = 200007;
int n, m, a[maxn], lp[maxn], rp[maxn]; 
ll f[maxn], sum[maxn];

void cf1994C() {
    cin >> n >> m;
    vector<int> pos[n+2];
    for (int i = 1; i <= n; ++i) {
    	cin >> a[i];        
    	f[i] = 0;
    }
    int l = 1, r = n;
    ll cur = 0;
    for (int i = 1; i <= n; ++i) {
        cur += a[i];
        while (cur > m) cur -= a[l++];
        lp[i] = l - 1; // (lp[i], i]
    }
    cur = 0;
    for (int i = n; i >= 1; --i) {
        cur += a[i];
        while (cur > m) cur -= a[r--];
        rp[i] = r + 1; // [i, r + 1)
        pos[r + 1].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        if (lp[i] == i) {
            f[i] = i;
        }
        else if (pos[i].size() > 0) {
            for (int v : pos[i]) {
                if (v > 0) f[i] += f[v-1] + 1;
            }
        }
        sum[i] = f[i] + sum[i-1];
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (lp[i] < i) {
            ans += (i - lp[i]);
            if (lp[i] > 0) ans += sum[i-1] - sum[lp[i] - 1];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) cf1994C();
}