#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 1000005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)


void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &v : a) cin >> v;
    int cur = 0, ans = 0, last = a[0], p = 0;
    while (p < n) {
        int i = p + 1;
        while (i < n && a[i] == a[p]) ++i;
        int len = a[p] - last, m = bit_width(1u * cur);
        if (len >= m) {
            ans += __builtin_popcount(cur);
            cur = 0;
        }
        else {
            ans += __builtin_popcount(cur & (1 << len) - 1);
            cur >>= len;
        }
        cur += i - p;
        last = a[p];
        p = i;
    }
    // [0...mx] + bit_width(cur)
    int width = a[n - 1] + bit_width(1u * cur), ones = ans + __builtin_popcount(cur);
    cout << width - ones << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
