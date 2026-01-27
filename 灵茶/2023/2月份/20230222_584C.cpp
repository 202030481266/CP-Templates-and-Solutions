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

char get(char c1, char c2) {
    int x = c1 - 'a', y = c2 - 'a';
    if (c1 == c2) {
        return 'a' + (x + 1) % 26;
    }
    if (x > y) swap(x, y);
    if ((y + 1) % 26 != x) { // not ('a','z')
        return 'a' + (y + 1) % 26;
    }
    return 'b';
}

void solve() {
    int n, t;
    cin >> n >> t;
    string a, b;
    cin >> a >> b;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == b[i]) ++cnt;
    }
    // cnt same, n - cnt is not same
    if (t < (n - cnt + 1) / 2) {
        cout << -1 << '\n';
        return;
    }
    vector<char> ans(n);
    if (t >= n - cnt) {
        int r = t - n + cnt;
        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) {
                if (r) {
                    ans[i] = get(a[i], b[i]);
                    --r;
                }
                else {
                    ans[i] = a[i];
                }
            }
            else {
                ans[i] = get(a[i], b[i]);
            }
        }
    }
    else {
        int r = t - (n - cnt + 1) / 2;
        int x = (r > cnt ? r - cnt : 0);
        x *= 2;
        if (n - cnt & 1) ++x;
        int last = 1;
        for (int i = 0; i < n; ++i) {
            if (a[i] == b[i]) {
                if (r) {
                    ans[i] = get(a[i], b[i]);
                    --r;
                }
                else ans[i] = a[i];
            }
            else {
                if (x) {
                    ans[i] = get(a[i], b[i]);
                    --x;
                }
                else {
                    if (last) ans[i] = b[i];
                    else ans[i] = a[i];
                    last ^= 1;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) cout << ans[i];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
