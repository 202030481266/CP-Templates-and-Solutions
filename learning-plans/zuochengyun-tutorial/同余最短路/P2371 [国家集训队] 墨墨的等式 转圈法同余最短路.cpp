#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
const int inf = 0x3f3f3f3f;
const long long llinf = 0x3f3f3f3f3f3f3f3f;
#define endl '\n'

int n;
ll l, r;

ll floor_div(ll a, ll b) {
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((a ^ b) < 0)) {
        q -= 1;
    }
    return q;
}

ll ceil_div(ll a, ll b) {
    ll q = a / b;
    ll r = a % b;
    if (r != 0 && ((a ^ b) > 0)) {
        q += 1;
    }
    return q;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> l >> r;
    vector<int> a;
    int t;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        if (t) a.push_back(t);
    }

    sort(a.begin(), a.end());
    n = a.size();

    vector<ll> dis(a[0], llinf);
    dis[0] = 0; // choose nothing
    for (int i = 0; i < n; ++i) {
        int g = gcd(a[0], a[i]);
        for (int j = 0; j < g; ++j) {
            int cur = j;
            for (int k = 0; k < 2; k += (cur == j ? 1 : 0)) {
                int nxt = (cur + a[i]) % a[0];
                if (dis[nxt] > dis[cur] + a[i]) {
                    dis[nxt] = dis[cur] + a[i];
                }
                cur = nxt;
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < a[0]; ++i) {
        if (dis[i] <= r) {
            ll left = max(0ll, ceil_div(l-dis[i], a[0])), right = floor_div(r-dis[i], a[0]);
            // [left, right]
            ans += right-left+1;
        }
    }    
    cout << ans << endl;
    return 0;
}