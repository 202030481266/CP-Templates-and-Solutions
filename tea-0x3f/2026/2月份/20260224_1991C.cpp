// Problem: C. Absolute Zero
// Contest: Codeforces - Pinely Round 4 (Div. 1 + Div. 2)
// URL: https://codeforces.com/problemset/problem/1991/C
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
using vl = vector<ll>;
using vll = vector<vector<ll>>;
static constexpr int MAXN = 200005;
static constexpr int MOD = 1e9 + 7;
static constexpr int INF = 0x3f3f3f3f;

// 观察：使用极差中点不断压缩极差

void solve() {
    int n;
    cin >> n;
    vi arr(n);
    for (int& v : arr) cin >> v;
    for (int i = 1; i < n; ++i) {
        if ((arr[i] & 1) ^ (arr[0] & 1)) {
            cout << -1 << '\n';
            return;
        }
    }
    int T = 40, flag = 0;
    vector<int> ans;
    while (T--) {
        int mx = *max_element(arr.begin(), arr.end());
        int mn = *min_element(arr.begin(), arr.end());
        if (mx == mn) {
            flag = 1;
            ans.push_back(mx);
            break;
        }
        else {
            int median = (mx + mn) / 2;
            ans.push_back(median);
            for (int& v : arr) v = abs(v - median);
        }
    }
    if (flag) {
        cout << ans.size() << '\n';
        for (int v : ans) cout << v << ' ';
        cout << '\n';
    }
    else cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}