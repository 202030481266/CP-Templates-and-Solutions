#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

static constexpr int MAXN = 100005;
static constexpr int MOD = 1000000007;

#define INT(x) static_cast<int>(x)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        ++a[i];
        if (i > 0) a[i] = max(a[i], a[i - 1]);
    }
    for (int i = n - 1; i > 0; --i) {
        a[i - 1] = max(a[i - 1], a[i] - 1);
    }
    cout << (accumulate(a.begin(), a.end(), 0ll) - sum - n) << '\n';
}