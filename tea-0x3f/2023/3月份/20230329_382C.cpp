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
    vi arr(n);
    for (int& v : arr) cin >> v;
    if (n == 1) {
        cout << -1 << '\n';
        return;
    }
    ranges::sort(arr);
    int d = arr[1] - arr[0];
    if (n == 2) {
        if (d % 2 == 0) {
            if (d > 0) {
                cout << 3 << '\n' << arr[0] - d << ' ' << arr[0] + d / 2 << ' ' << arr[n - 1] + d << '\n';
            }
            else cout << 1 << '\n' << arr[0] << '\n';
        }
        else cout << 2 << '\n' << arr[0] - d << ' ' << arr[n - 1] + d << '\n';
        return;
    }
    auto cal = [&](int d) -> int {
        int p = -1;
        for (int i = 1; i < n; ++i)
        {
            if (arr[i] - arr[i - 1] != d)
            {
                if (p != -1 || arr[i] - arr[i - 1] != 2 * d)
                {
                    return -2;
                }
                p = i;
            }
        }
        return p;
    };
    int p = cal(d);
    if (p == -1) {
        if (d > 0) {
            cout << 2 << '\n' << arr[0] - d << ' ' << arr[n - 1] + d << '\n';
        }
        else cout << 1 << '\n' << arr[0] << '\n';
        return;
    }
    if (p > -1) {
        cout << 1 << '\n' << arr[p] - d << '\n';
        return;
    }
    if (d % 2 == 0) p = cal(d / 2);
    if (p == -2) cout << 0 << '\n';
    else cout << 1 << '\n' << arr[p] - d / 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}