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


void solve() {
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    vl asc(n, LLINF);
    asc[n - 1] = 0;
    ll cost = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (arr[i] > arr[i + 1]) {
            cost += arr[i] - arr[i + 1];
        }
        if (arr[i] < cost) break;
        else asc[i] = cost;
    }
    vl dsc(n, LLINF);
    dsc[0] = 0;
    cost = 0;
    for (int i = 1; i < n; ++i) {
        if (arr[i] > arr[i - 1]) {
            cost += arr[i] - arr[i - 1];
        }
        if (arr[i] < cost) break;
        else dsc[i] = cost;
    }
    if (asc[0] == 0 || dsc[n - 1] == 0) {
        cout << "YES" << '\n';
        return;
    }
    vi pre(n), suf(n);
    pre[0] = arr[0];
    suf[n - 1] = arr[n - 1];
    for (int i = 1; i < n; ++i) pre[i] = min(pre[i - 1], arr[i]);
    for (int i = n - 2; i >= 0; --i) suf[i] = min(suf[i + 1], arr[i]);
    
    // debug
    //for (int i = 0; i < n; ++i) cout << asc[i] << ' '; cout << '\n';
    //for (int i = 0; i < n; ++i) cout << dsc[i] << ' '; cout << '\n';
    //for (int i = 0; i < n; ++i) cout << pre[i] << ' '; cout << '\n';
    //for (int i = 0; i < n; ++i) cout << suf[i] << ' '; cout << '\n';

    for (int i = 0; i < n - 1; ++i) {
        if (dsc[i] == LLINF || asc[i + 1] == LLINF) continue;
        if (1LL * min(arr[i], arr[i + 1]) < dsc[i] + asc[i + 1]) continue;
        if (pre[i] < asc[i + 1] || suf[i + 1] < dsc[i]) continue;
        cout << "YES" << '\n';
        return;
    }
    cout << "NO" << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--)
        solve();
}

