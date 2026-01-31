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
    int n, x;
    cin >> n >> x;
    if (x == 0) {
        if (n == 1) cout << -1 << '\n';
        else cout << (n & 1 ? n + 3 : n) << '\n';
        return;
    }
    if (x == 1) {
        cout << (n & 1 ? n : n + 3) << '\n';
        return;
    }
    int b = popcount(1u * x);
    if (b >= n) cout << x << '\n';
    else {
        if (n - b & 1) cout << (x + n - b + 1) << '\n';
        else cout << (x + n - b)  << '\n';
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
}
