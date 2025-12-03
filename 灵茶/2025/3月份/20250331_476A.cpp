#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
static constexpr int mod = 1e9 + 7;
static constexpr int inf = 0x3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    if (n < m) {
        cout << -1 << '\n';
        return;
    }
    int r = n % m;
    int k = (n - 2 * r) / (2 * m);
    int x = k * m + r;
    cout << n - x << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    return 0;
}