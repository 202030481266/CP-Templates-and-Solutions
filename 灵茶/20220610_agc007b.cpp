#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vector<int>>;

static constexpr int MAXN = 200005;
static constexpr int INF = 0x3f3f3f3f;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    vector<int> val(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        val[arr[i]] = i - 1;
    }
    vector<int> a(n + 1), b(n + 1);
    a[1] = 0;
    b[1] = val[1];
    for (int i = 2; i <= n; ++i) {
        if (val[i - 1] > val[i]) {
            a[i] = a[i - 1] + 1;
            b[i] = val[i] - a[i];
        }
        else {
            b[i] = b[i - 1] - 1;
            a[i] = val[i] - b[i];
        }
    }
    int mn = *ranges::min_element(a);
    if (mn <= 0) {
        mn = abs(mn) + 1;
        for (int &v : a) v += mn;
    }
    mn = *ranges::min_element(b);
    if (mn <= 0) {
        mn = abs(mn) + 1;
        for (int &v : b) v += mn;
    }
    for (int i = 1; i <= n; ++i) cout << a[i] << (i == n ? '\n' : ' ');
    for (int i = 1; i <= n; ++i) cout << b[i] << (i == n ? '\n' : ' ');
    cout << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}
