#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (k == 1) {
        int mx = 0;
        for (int i = 1; i < n - 1; ++i) mx = max(mx, a[i]);
        cout << max(mx + max(a[0], a[n - 1]), a[n - 1] + a[0]) << '\n';
        return;
    }
    priority_queue<int, vector<int>, greater<>> q;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        if (q.size() < k + 1) {
            sum += a[i];
            q.push(a[i]);
        }
        else {
            if (q.top() < a[i]) {
                sum -= q.top();
                q.pop();
                q.push(a[i]);
                sum += a[i];
            }
        }
    }
    cout << sum << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}