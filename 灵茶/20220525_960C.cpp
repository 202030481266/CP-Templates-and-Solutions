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
    int x, d, n = 0;
    cin >> x >> d;
    vector<int> arr;
    for (int i = 0; i < 32; ++i) {
        if (x >> i & 1) {
            arr.push_back(i);
            n += i + 1;
        }
    }
    ll last = 1;
    cout << n << '\n';
    for (int v : arr) {
        while (v--) cout << last << ' ';
        last += d;
    }
    for (int i = 0; i < arr.size(); ++i, last += d) {
        cout << last << (i == arr.size() - 1 ? "\n" : " ");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}