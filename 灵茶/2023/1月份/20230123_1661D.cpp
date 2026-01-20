#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vl = vector<long long>;
using vll = vector<vector<long long>>;

void solve() {
    int n, m;
    cin >> n >> m;
    vl a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll c = 0, pc = 0;
    vi pos;
    vl cnt, con;
    ll ans = 0, p = 0;
    for (int i = n; i >= 1; --i) {
        while (p < pos.size() && pos[p] >= i + m) {
            c -= cnt[p];
            pc -= con[p];
            ++p;
        }
        ll tot = c * i + pc;
        if (tot < a[i]) {
            int k = min(m, i);
            ll t = (a[i] - tot + k - 1) / k;
            pos.push_back(i);
            cnt.push_back(t);
            con.push_back(t * (i - k));
            ans += t;
            c += cnt.back();
            pc += con.back();
        }
    }
    cout << ans << '\n';
} 


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
